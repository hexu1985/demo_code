/**
 *  occipool - Demontrating the Connection Pool interface of OCCI.
 *
 *  DESCRIPTION :
 *    This program demonstates the creating and using of connection pool in the 
 *    database and fetching records of a table.
 * 
 */

#include <iostream>
#include <occi.h>
using namespace oracle::occi;
using namespace std;

class occipool 
{
private:

    Environment *env;
    Connection *con;
    Statement *stmt;
public :
    /**
     * Constructor for the occipool test case.
     */
    occipool () 
    {
        env = Environment::createEnvironment (Environment::DEFAULT);
    }// end of constructor occipool ()

    /**
     * Destructor for the occipool test case.
     */
    ~occipool () 
    {
        Environment::terminateEnvironment (env);
    }  // end of ~occipool ()

    /**
     * The testing logic of the test case.
     */
    dvoid select ()
    {
        cout << "occipool - Selecting records using ConnectionPool interface" <<
            endl;
        const string poolUserName = "SCOTT";
        const string poolPassword = "TIGER";
        const string connectString = "";
        const string username = "SCOTT";
        const string passWord = "TIGER";
        unsigned int maxConn = 5;
        unsigned int minConn = 3;
        unsigned int incrConn = 2;
        ConnectionPool *connPool = env->createConnectionPool
            (poolUserName, poolPassword, connectString, minConn, maxConn, incrConn);
        try{
            if (connPool)
                cout << "SUCCESS - createConnectionPool" << endl;
            else
                cout << "FAILURE - createConnectionPool" << endl;
            con = connPool->createConnection (username, passWord);
            if (con)
                cout << "SUCCESS - createConnection" << endl;
            else
                cout << "FAILURE - createConnection" << endl;
        }catch(SQLException ex)
        {
            cout<<"Exception thrown for createConnectionPool"<<endl;
            cout<<"Error number: "<<  ex.getErrorCode() << endl;
            cout<<ex.getMessage() << endl;
        }

        cout << "retrieving the data" << endl;
        stmt = con->createStatement 
            ("SELECT author_id, author_name FROM author_tab");
        ResultSet *rset = stmt->executeQuery();
        while (rset->next())
        {
            cout << "author_id:" << rset->getInt (1) << endl;
            cout << "author_name:" << rset->getString (2) << endl;
        }
        stmt->closeResultSet (rset);
        con->terminateStatement (stmt);
        connPool->terminateConnection (con);
        env->terminateConnectionPool (connPool);

        cout << "occipool - done" << endl;
    } // end of test (Connection *)

}; // end of class occipool

int main (void)
{
    string user = "SCOTT";
    string passwd = "TIGER";
    string db = "";

    occipool *demo = new occipool ();

    demo->select();
    delete demo;

}// end of main ()

