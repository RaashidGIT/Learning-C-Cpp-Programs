//program to display planet's info using enumeration(enums) in c++
# include<iostream>
using namespace std;

enum planets
{
    Mercury,Venus,Earth,Mars,
    Jupiter,Saturn,Uranus,Neptune
};

int main()
{
  planets planet=Mercury;
  switch(planet)
  {
      case Mercury: cout<<"Mercury: Closest to the Sun, approximately 58 million km.";break;
      case Venus: cout<<"Venus: Second planet from the Sun, approximately 108 million km.";break;
      case Earth: cout<<"Earth: Third planet from the Sun, approximately 150 million km.";break;
      case Mars: cout<<"Mars: Fourth planet from the Sun, approximately 228 million km.";break;
      case Jupiter: cout<<"Jupiter: Fifth planet from the Sun, approximately 779 million km.";break;
      case Saturn: cout<<"Saturn: Sixth planet from the Sun, approximately 1.4 billion km.";break;
      case Uranus: cout<<"Uranus: Seventh planet from the Sun, approximately 2.9 billion km.";break;
      case Neptune: cout<<"Neptune: Eighth planet from the Sun, approximately 4.5 billion km.";break;
  }

return 0;
}