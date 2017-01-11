include <iostream>

using namespace std;

int main()
{
        cout<<"enter 6 digitr of the equation: "
        int a;
        int b;
        int c;
        int d;
        int e;
        int f;

        cin>>a>>b>>c>>d>>e>>f;

        cout<<"x == "<< (c*e -f*b)/(a*e - d*b);
	cout<<"\ny == "<< (a*f - d*c)/(a*e - d*b)<<'\n';

}
