/**
 * occistrm - Demonstrating the usage of streams for VARCHAR2 data 
 *
 * Description
 *   This demo program selects VARCHAR2 data using stream operations.
 */

#include <iostream>
#include <occi.h>
using namespace oracle::occi;
using namespace std;

class occistrm
{
private:

    Environment *env;
    Connection *conn;

public:

    occistrm (string user, string passwd, string db) throw (SQLException)
    {
        env = Environment::createEnvironment (Environment::DEFAULT);
        conn = env->createConnection (user, passwd, db);
    }// end of constructor occistrm (string, string, string)

    ~occistrm () throw (SQLException)
    {
        env->terminateConnection (conn);
        Environment::terminateEnvironment (env);
    }// end of destructor

    /**
     * displaying all the rows in the table
     */
    void displayAllRows ()
    {
        Statement *stmt = conn->createStatement (
                "SELECT summary FROM book WHERE bookid = 11");
        stmt->execute ();
        ResultSet *rs = stmt->getResultSet ();
        rs->setCharacterStreamMode(1, 4000);
        char buffer[500];
        int length = 0; 
        unsigned int size = 500;

        while (rs->next ())
        {
            Stream *stream = rs->getStream (1);
            while( (length=stream->readBuffer(buffer, size))!=-1)
            {
                cout << "Read " << length << " bytes from stream" << endl;
            }
        }
        stmt->closeResultSet (rs);
        conn->terminateStatement (stmt);
    }// end of updateRow (string);

}; // end of class occistrm


int main (void)
{
    string user = "SCOTT";
    string passwd = "TIGER";
    string db = "";

    cout << "occistrm - Exhibiting usage of streams for VARCHAR2 data" 
        << endl;
    occistrm *demo = new occistrm (user, passwd, db);

    demo->displayAllRows ();

    delete (demo);
    cout << "occistrm - done" << endl;
}// end of int main (void);
