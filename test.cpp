#include<iostream>

void sort(int* arr,int size)
{
	bool flag=false;
	for(int i=0;i<size-1;i++)
	{
		for(int j=0;j<size-1-i;j++)
		{
			if(arr[j]>arr[j+1])
			{
				int temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
				flag=true;
			}
		}
		if(flag)
			break;
	}
}

void print(int* arr,int size)
{
	for(int i=0;i<size;i++)
		std::cout<<arr[i]<<" ";
	std::cout<<std::endl;
}

void test()
{
	std::cout<<"hello world"<<std::endl;
	int arr[]={1,2,3,4,5};
	size_t size=sizeof(arr)/sizeof(arr[0]);
	sort(arr,size);
	print(arr,size);
}

int main()
{
	test();
	return 0;
}
