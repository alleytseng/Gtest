#include <iostream>
using namespace std;
#include <string>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;

class User{
public:
	string Name;
	virtual void SetName(string tmpName){Name=tmpName;}
	virtual string GetName(){return Name;}
	virtual bool IsAdmin(){	
		string admin="alley";
		if(admin.compare(Name)==0)
			return true;
		return false;
	}
};

class MockUser:public User
{
	public:
	MOCK_METHOD1(SetName, void(string tmpName));
	MOCK_METHOD0(GetName, string());
	MOCK_METHOD0(IsAdmin, bool());
};

class Reservation{
public:
	User &BookingName;
	Reservation(User user):BookingName(user){}
	bool CanBeCancelBy(User &user){
		if(user.IsAdmin()==true){
			//do some thing...
			return true;
		}
		if(user.GetName().compare(BookingName.GetName())==0){
			//do some thing...
			return true;
		}
		return false;
	}
};


TEST(CanBeCancelBy, UserIsAdmin_ReturnTrue)
{
	//Arrange	
	User admin;
	admin.SetName("alley");
	User user;
	user.SetName("Maggie");
	Reservation r1(user);

	//Act
	bool result=r1.CanBeCancelBy(admin);
	//Assert
	
	EXPECT_EQ(result, 0);
	cout<<"####### After assertion.\n";
}
TEST(CanBeCancelBy, SameUserCancellingTheReservation_ReturnTrue)
{
	//Arrrange
	User user;
	user.SetName("Maggie");
	Reservation r1(user);
	//Act
	bool result=r1.CanBeCancelBy(user);
	//Assert
	EXPECT_TRUE(result);
}
TEST(CanBeCancelBy, AnotherUserCancellingTheReservation_ReturnFalse)
{
	//Arrrange
	User user1;
	user1.SetName("Maggie");
	User user2;
	user2.SetName("Tom");
	Reservation r1(user1);
	//Act
	bool result=r1.CanBeCancelBy(user2);
	//Assert
	EXPECT_FALSE(result);
}
bool dummyisadmin(){
	cout<<"Dummy Login gets called.\n";
	return  true;
}
TEST(CanBeCancelBy, MockUserIsAdmin_ReturnTrue)
{
	//Arrange	
	MockUser admin;
	User a1;
	a1.SetName("a1");
	Reservation r1(a1);
	EXPECT_CALL(admin, IsAdmin()).Times(1).WillOnce(Return(true));
	//ON_CALL(admin, IsAdmin()).WillByDefault(Return(true));
	//EXPECT_CALL(admin, IsAdmin()).
	//Times(1).
	//WillOnce(InvokeWithoutArgs(dummyisadmin));
	//Act
	bool result=r1.CanBeCancelBy(admin);
	//Assert
	EXPECT_EQ(result, 1);
}

int main()
{	User num1;
	num1.SetName("n1");
	cout<<num1.GetName()<<" is ";
	(num1.IsAdmin()==1)?cout<<"":cout<<"not ";
	cout<<"admin.\n";
	User num2;
	num2.SetName("n2");
	Reservation r1(num1);
	cout<<num2.GetName();
	(r1.CanBeCancelBy(num2)==1)?cout<<" can ":cout<<" cant't ";
	cout<<"cancel "<<r1.BookingName.GetName()<<"'s reservation.\n";

	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}