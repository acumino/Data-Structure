#include <bits/stdc++.h>
using namespace std;

void createTree(int segTree[], int input[], int low ,int high, int pos)
{
	if(low==high)
	{
		segTree[pos] = input[low];
		return ;
	}
	
	int mid = low + (high-low)/2;
	createTree(segTree,input,low,mid,pos*2+1);
	createTree(segTree,input,mid+1,high,pos*2+2);
	// the work u want ot have withe the seg Tree
	// actual associative function of Seg Tree
	// any associave function can be performed
	// using segTree in O(log(n))
	// segTree[pos] = segTree[pos*2+1]+segTree[pos*2+2]; //range sum
	segTree[pos] = min(segTree[pos*2+1],segTree[pos*2+2]); // range max ,min
}

int rangeQuery(int segTree[],int qlow, int qhigh, int low ,int high,int pos)
{
	
	if(qlow<=low&&qhigh>=high)
	{
		return segTree[pos];
	}
	if(qlow>high||qhigh<low)
	{
		// return 0; //range sum
		return INT_MAX; //range min 
		// return INT_MIN; //range max
	}
	int mid = low + (high-low)/2;
	int a = rangeQuery(segTree,qlow,qhigh,low,mid,2*pos+1);
	int b = rangeQuery(segTree,qlow,qhigh,mid+1,high,2*pos+2);
	// return a+b; //range sum
	return min(a,b); // range min,max
}


void updateQuery(int segTree[],int low,int high, int i,int value, int pos)
{
	
	// i is the update position in array
	// value is the update value;
	if(i<low||i>high)
		return ;
	
	if(low==high)
	{
		segTree[pos] = value;
		return ;
	}
	int mid = low + (high-low)/2;
	if(i<=mid)
		updateQuery(segTree,low,mid,i,value,pos*2+1);
	else
		updateQuery(segTree,mid+1,high,i,value,pos*2+2);
	
	// segTree[pos] = segTree[pos*2+1]+segTree[pos*2+2]; 
	segTree[pos] = min(segTree[pos*2+1],segTree[pos*2+2]);// range max ,min
	
}




int main() {
	// your code goes here
	
	int arr[] = {1, 3, 5, 7, 9, 11};  
    int n = sizeof(arr)/sizeof(arr[0]);  
    int segTree[n*2-1]={0};
    // for(int i=0;i<n*2-1;i++)
    // 	segTree[i] = INT_MAX;
    createTree(segTree,arr,0,n-1,0);
 //   for(int i=0;i<n*2-1;i++)
 //   	cout<<segTree[i]<<" ";
	// cout<<endl;
    // all queries
    updateQuery(segTree,0,n-1,1,10,0);
    for(int i=0;i<n;i++)
    {
    	cout<<rangeQuery(segTree,0,i,0,n-1,0)<<" ";
    }
    
    
    
    
	
	
	return 0;
}
