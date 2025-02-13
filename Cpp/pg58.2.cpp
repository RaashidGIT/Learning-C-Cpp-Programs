//Volume adjuster program using getters & setters in c++
//Getters and setters allow you to enforce certain rules or conditions on the data being accessed or modified.
# include<iostream>
using namespace std;

class sony
{
private:
    int volume;
public:
    sony(int avolume)
    {
      setVolume(avolume);
    }
    int getVolume()
    {
        return volume;
    }
    void setVolume(int avolume)
    {
        if(avolume>50)
        {
            volume=50;
        }
        else if(avolume<0)
        {
            volume=0;
        }
        else
        {
            volume=avolume;
        }
    }
};

int main()
{
   cout<<"***********Volume adjuster***********\n";
   sony shaker(0);
   int temp;
   cout<<"Current volume:"<<shaker.getVolume();
   cout<<endl;
   cout<<"Enter the volume change:";
   cin>>temp;
   shaker.setVolume(temp);
   cout<<"Volume is now:"<<shaker.getVolume();
   cout<<"\n*************************************\n";
   return 0;
}