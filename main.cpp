#include<bits/stdc++.h>
using namespace std;
#define usi unsigned long long

struct node 
{
    int data;
    struct node* left;
    struct node* right;
};

struct node* newNode(int data)
{
    // Allocate memory for new node
    struct node* node
        = (struct node*)malloc(sizeof(struct node));
 
    // Assign data to this node
    node->data = data;
 
    // Initialize left and
    // right children as NULL
    node->left = NULL;
    node->right = NULL;
    return (node);
}

node *root=newNode(-1);

void count_freq(string s,vector<pair<int,string>> &freq)
{
    int n=s.length();
    for(int i=0;i<n;i++)
    {
        freq[s[i]].first++;
    }
    return;
}

void make_huffman_tree(priority_queue <pair<int,node*>, vector<pair<int,node*>>, greater<pair<int,node*>>> pq)
{
    pair<int,node*>x=pq.top();
    pq.pop();
    pair<int,node*>y=pq.top();
    pq.pop();
    if(pq.empty())
    {
        root->left=x.second;
        root->right=y.second;
        return;
    }
    node *com=newNode(-1);
    com->left=x.second;
    com->right=y.second;
    pq.push({x.first+y.first,com});
    make_huffman_tree(pq);
    return;
}

void make_encode__dict(vector<pair<int,string>> &freq,string t,node *head)
{
    if(head->data!=-1)
    {
        freq[head->data].second=t;
        return;
    }
    t.push_back('0');
    make_encode__dict(freq,t,head->left);
    t.pop_back();
    t.push_back('1');
    make_encode__dict(freq,t,head->right);
    return;
}

void make_pq(priority_queue <pair<int,node*>, vector<pair<int,node*>>, greater<pair<int,node*>>> &pq, vector<pair<int,string>> &freq)
{
    for(int i=0;i<128;i++)
    {
        if(freq[i].first==0) continue;
        node *t=newNode(i);
        pq.push({freq[i].first,t});
    }
    return;
}

void make_decode_dict(map<string,int> &decode_dict,vector<pair<int,string>> &freq)
{
    for(int i=0;i<128;i++)
    {
        if(freq[i].first!=0)
        {
            decode_dict[freq[i].second]=i;
        }
    }
    return;
}

void encode(string &s,vector<pair<int,string>> &freq,vector<usi> &encoded_text)
{
    int c=0;
    int n=s.length();
    usi t=1;
    for(int i=0;i<n;i++)
    {
        string a=freq[s[i]].second;
        reverse(a.begin(),a.end());
        while(a.size()!=0)
        {
            t=(t<<1);
            if(a.back()=='1') t++;
            a.pop_back();
            c++;
            if(c==63)
            {
                encoded_text.push_back(t);
                t=1;
                c=0;
            }
        }
    }
    if(t!=1)
    {
        encoded_text.push_back(t);
    }
    return;
}

void print_encoded_text(vector<usi> &encoded_text)
{
    for(usi i:encoded_text) cout<<i<<endl;
    return;
}

string num_to_bin(usi n)
{
    string ans="";
    while(n>0)
    {
        if(n%2!=0) ans.push_back('1');
        else ans.push_back('0');
        n/=2;
    }
    reverse(ans.begin(),ans.end());
    return ans;
}

void decode(vector<usi> &encoded_text,map<string,int> &decode_dict,string &decoded_text)
{
    decoded_text="";
    int n=encoded_text.size();
    string r="";
    for(int i=0;i<n;i++)
    {
        string t=num_to_bin(encoded_text[i]);
        int a=t.length();
        for(int j=1;j<a;j++)
        {
            r.push_back(t[j]);
            if(decode_dict.find(r)!=decode_dict.end())
            {
                decoded_text.push_back(decode_dict[r]);
                r="";
            }
        }
    }
    return ;
}

void print_decoded_text(string &decoded_text)
{
    for(char ch:decoded_text) cout<<ch;
    cout<<endl;
    return;
}

int main()
{
    while(1)
    {
        string s;
        string line;
        cout<<"Please enter the text.(Write done123 on new line when you are done)"<<endl;
        while (getline(cin, line)) 
        {
            if(line=="done123") break;
            s+=line + "\n"; 
        }
        s.pop_back();

        vector<pair<int,string>> freq(128,{0,""});
        priority_queue <pair<int,node*>, vector<pair<int,node*>>, greater<pair<int,node*>>> pq;
        map<string,int> decode_dict;
        vector<usi> encoded_text;
        string decoded_text;

        count_freq(s,freq);
        make_pq(pq,freq);
        make_huffman_tree(pq);
        make_encode__dict(freq,"",root);
        make_decode_dict(decode_dict,freq);
        encode(s,freq,encoded_text);
        decode(encoded_text,decode_dict,decoded_text);
        cout<<"Press 1 to show encoded text or any other number to continue"<<endl;
        int t;
        cin>>t;
        if(t==1)
        print_encoded_text(encoded_text);
        cout<<"Press 1 to show decoded text or any other number to continue"<<endl;
        cin>>t;
        if(t==1)
        print_decoded_text(decoded_text);
        cout<<"Number of characters in original text:"<<s.length()<<endl;
        cout<<"Number of elements in encoded array:"<<encoded_text.size()<<endl;
        cout<<"Press 1 to exit and any other number to continue"<<endl;
        cin>>t;
        if(t==1) break;
    }
    return 0;
}