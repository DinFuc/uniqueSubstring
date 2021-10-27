#define ff(i , a, b) for(int i = a; i <= int(b); i++)
typedef long long ll;
const ll MAXN = 1e4 + 7;
const ll INF = 1e9 + 7;
const ll base = 311;
///construct a segment tree
//{
    string SegTree[4*MAXN];
    void Update(int id , int low , int high , int pos, char val)
    {
        if (low == high)
        {
            SegTree[pos] += val;
            return;
        }
        int mid = (low + high)/2;
        if (id <= mid) Update(id , low , mid , 2*pos + 1 , val);
        else Update(id , mid + 1 , high , 2*pos + 2 , val);
        SegTree[pos] = SegTree[2*pos + 1] + SegTree[2*pos + 2];
    }
    void query(int l , int r , int low , int high , int pos , string &res)
    {
        if (low > r || high < l) return;
        if (low >= l && high <= r)
        {
            res+=SegTree[pos];
            return;
        }
        int mid = (low + high)/2;
        query(l , r , low , mid , 2*pos + 1 , res);
        query(l , r , mid + 1 , high , 2*pos + 2 , res);
    }
//}
/// the binary search function
bool f(int m , string str)
{
    ll hash_value = 0 , value = 1;
    ff(i , 1 , m - 1) value = value*base%INF;
    priority_queue<ll> check;
    ff(i , 1 , int(str.size()) - 1)
    {
        if (i <= m)
        {
            hash_value = (hash_value*base + str[i])%INF;
            if (i == m) check.push(hash_value);
        }
        else
        {
            hash_value = ((hash_value - str[i - m]*value)*base + str[i])%INF;
            if (hash_value < 0) hash_value+= INF;
            check.push(hash_value);
        }
    }
 
    while(!check.empty())
    {
        ll tmp = check.top();
        check.pop();
        int cnt = 0;
        while(!check.empty() && check.top() == tmp) check.pop() , cnt++;
        if (cnt == 0) return true;
    }
    return false;
}
/// the function to find substrings satisfy the condition
vector<string> storage;
void substring_condition(int len , string str)
{
    ll hash_value = 0 , value = 1;
    ff(i , 1 , len - 1) value = value*base%INF;
    map<ll , bool> check;
    ff(i , 1 , int(str.size()) - 1)
    {
        if (i <= len)
        {
            hash_value = (hash_value*base + str[i])%INF;
            if (i == len) check.insert(pair<ll , bool> (hash_value , true));
        }
        else
        {
            hash_value = ((hash_value - str[i - len]*value)*base + str[i])%INF;
            if (hash_value < 0) hash_value+= INF;
            if (!check.count(hash_value)) check.insert(pair<ll , bool> (hash_value , true));
            else check[hash_value] = false;
        }
    }
    hash_value = 0;
    ff(i , 1 , int(str.size()) - 1)
    {
        if (i <= len) hash_value = (hash_value*base + str[i])%INF;
        else hash_value = ((hash_value - str[i - len]*value)*base + str[i])%INF;
        if (hash_value < 0) hash_value+= INF;
        if (check[hash_value])
        {
            string res;
            query(i - len + 1 , i , 0 , MAXN - 1 , 0 , res);
            storage.push_back(res);
        }
    }
}
/// find the answer for problem
//{
    bool compare(string a , string b)
    {
        return a < b;
    }
    string find_the_answer()
    {
        sort(storage.begin() , storage.end() , compare);
        return storage[0];
    }
//}
/// the main function
string uniqueSubstring(string str)
{
    if (int(str.size()) == 1) return str;
    str = "#" + str;
    ff(i , 0 , int(str.size()) - 1) Update(i , 0 , MAXN - 1 , 0 , str[i]); //Update segment tree
    int l = 1 , r = int(str.size()) - 1 , res;
    while(r >= l)
    {
        int m = (l + r)/2;
        if (f(m , str)) res = m , r = m - 1;
        else l = m + 1;
    }
    //cout << res;
    substring_condition(res , str);
    return find_the_answer();
}
