#include <iostream>
using namespace std;
#include "gtest/gtest.h"
#include "gmock/gmock.h"
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;

class DataBaseConnect
{
public:
	virtual bool login(string username, string passward){return true;}
	virtual bool login2(string username, string passward){return true;}
	virtual bool logout(string username){return true;}
	virtual int fetchRecord(){return -1;}
};

class MockDB: public DataBaseConnect
{
public:
	MOCK_METHOD0(fetchRecord, int());
	MOCK_METHOD1(logout, bool (string username));
	MOCK_METHOD2(login, bool (string username, string password));
	MOCK_METHOD2(login2, bool (string username, string password));
};

class MyDatabase
{
	DataBaseConnect &dbC;
public:
	MyDatabase(DataBaseConnect & _dbC):dbC(_dbC){}
	int Init(string username, string password)
	{
		int rvalue=rand()%2;
		if(rvalue == 0)
		{
			if(dbC.login(username, password) != true)
			{
				if(dbC.login(username, password) != true)
				{
					//cout<<"DB FAILURE"<<endl;
					cout<<"DB FAILURE 2nd TIME"<<endl;
					return -1;
				}
			}
			else
			{
				cout<<"DB SUCCESS"<<endl;
				return 1;
			}
		}
		else
		{
			return dbC.login2(username, password);
		}

	}
};
TEST(MyDBTest, LoginTest)
{
	MockDB mdb;
	MyDatabase db(mdb);
	//EXPECT_CALL(mdb, login(_, _)).Times(1).WillOnce(Return(true));
	ON_CALL(mdb, login(_, _)).WillByDefault(Return(true));
	ON_CALL(mdb, login2(_, _)).WillByDefault(Return(true));
	//int retValue =1;// db.Init("Terminator", "I'm Back");
	int retValue = db.Init("Terminator", "I'm Back");
	EXPECT_EQ(retValue, 1);
}
int main(int argc,char **argv)
{
	testing::InitGoogleTest(&argc,argv);
	RUN_ALL_TESTS();
	return 0;
}