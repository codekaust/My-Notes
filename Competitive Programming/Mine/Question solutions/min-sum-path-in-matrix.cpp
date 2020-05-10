// BOTTOM UP

void print_(vector<vector<int>> a){
    for(auto x:a){
        for(auto y:x){
            cout<<y<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int Solution::minPathSum(vector<vector<int> > &A) {
    int n=A.size(), k=A[0].size();
    
    vector<vector<int> > dp(n+1);
    for(int i=0; i<n+1; i++){
        vector<int> tmp(k+1, INT_MAX);
        dp[i] = tmp;
    }
    
    dp[n-1][k-1]=A[n-1][k-1];
    // dp[n-2][k-1]=dp[n-1][k-1]+A[n-2][k-1];
    // dp[n-1][k-2]=dp[n-1][k-1]+A[n-1][k-2];
    
    // print_(dp);
    
    int n1,k1;
    for(int i=1; i<=n+k-2; i++){
        for(int j=0; j<=i; j++){
            
            n1=n-1-j;
            k1=k-1-(i-j);
            
            if(n1>=0&&k1>=0)
                dp[n1][k1]=A[n1][k1]+min(dp[n1][k1+1],dp[n1+1][k1]);
        }        
    }
    
    return dp[0][0];
}
