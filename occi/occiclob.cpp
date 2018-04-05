#include <iostream>
#include <string.h>
#include <occi.h>

using namespace oracle::occi;
using namespace std;

/**
 * The demo sample has starts from startDemo method.  This method is called 
 * by main.  startDemo calls other methods, the supporting methods for 
 * startDemo are,
 * insertRows    -  inserts the rows into the table1
 * deleteRows    -  delete the rows inserted
 * insertClob    - Inserts a clob and an empty_clob
 * populateClob  - populates a given clob
 * dumpClob      - prints the clob as an integer stream
 */

class  demoClob
{
private:  
    string username;
    string password;
    string url;

    void insertRows (Connection *conn) throw (SQLException)
    {
        Statement *stmt = conn->createStatement ("INSERT INTO print_media(product_id,ad_id,ad_composite,ad_sourcetext) VALUES (3333,11001,'10001','SHE')");
        stmt->executeUpdate();
        stmt->setSQL ("INSERT INTO print_media(product_id,ad_id,ad_composite,ad_sourcetext) VALUES (4444,11001,'1010','HEM')");
        stmt->executeUpdate();
        conn->commit();
        conn->terminateStatement (stmt);

    }

    void deleteRows (Connection *conn) throw (SQLException)
    {
        Statement *stmt = conn->createStatement ("DELETE print_media WHERE product_id=3333 AND ad_id=11001");
        stmt->executeUpdate();
        stmt->setSQL("DELETE print_media WHERE product_id=4444 AND ad_id=11001");
        stmt->executeUpdate();
        conn->commit();
        conn->terminateStatement (stmt);

    }

    /**
     * populating the clob;
     */
    void populateClob (Clob &clob, int size) throw (SQLException)
    {
        Stream *outstream = clob.getStream (1,0);
        char *buffer = new char[size];

        memset (buffer,'H', size);
        outstream->writeBuffer (buffer, size);
        char *c = (char *)"";
        outstream->writeLastBuffer (c,0);
        delete (buffer);
        clob.closeStream (outstream);
    }

    /**
     * printing the clob data as integer stream
     */
    void dumpClob (Clob &clob, int size) throw (SQLException)
    {
        Stream *instream = clob.getStream (1,0);
        char *buffer = new char[size];
        memset (buffer, NULL, size);

        instream->readBuffer (buffer, size);
        cout << "dumping clob: ";
        for (int i = 0; i < size; ++i)
            cout << (char) buffer[i];
        cout << endl;

        delete (buffer);
        clob.closeStream (instream);
    }



    /**
     * public methods
     */
public:
    demoClob ()
    {
        /**
         * default values of username & password
         */
        username = "SCOTT";
        password = "TIGER";
        url = "";
    }

    void setUsername (string u)
    {
        username = u;
    }

    void setPassword (string p)
    {
        password = p;
    }

    void setUrl (string u)
    {
        url = u;
    }

    void runSample () throw (SQLException)
    {
        Environment *env = Environment::createEnvironment (
                Environment::DEFAULT);
        try
        {
            Connection *conn = env->createConnection (username, password, url);
            Statement *stmt1;
            insertRows (conn);
            /**
             * Reading a populated clob & printing its property.
             */
            string sqlQuery = "SELECT  ad_sourcetext FROM print_media WHERE product_id=3333";
            Statement *stmt = conn->createStatement (sqlQuery);

            ResultSet *rset = stmt->executeQuery ();
            while (rset->next ())
            {
                Clob clob = rset->getClob (1);
                cout << "Opening the clob in Read only mode" << endl;
                clob.open (OCCI_LOB_READONLY);
                int clobLength=clob.length ();
                cout << "Length of the clob is: " << clobLength << endl;
                dumpClob (clob, clobLength);
                clob.close ();
            }
            stmt->closeResultSet (rset);

            /**
             * Reading a populated clob & printing its property.
             */
            stmt->setSQL ("SELECT ad_sourcetext FROM print_media WHERE product_id =4444 FOR UPDATE");
            rset = stmt->executeQuery ();
            while (rset->next ())
            {
                Clob clob = rset->getClob (1);
                cout << "Opening the clob in read write mode" << endl;
                clob.open (OCCI_LOB_READWRITE);
                cout << "Populating the clob" << endl;
                populateClob (clob, 20);
                int clobLength=clob.length ();
                cout << "Length of the clob is: " << clobLength << endl;
                dumpClob (clob, clobLength);
                clob.close ();
            }
            stmt->closeResultSet (rset);
            conn->terminateStatement (stmt);
            deleteRows(conn);
            env->terminateConnection (conn);
        }
        catch (SQLException ea)
        {
            cout << ea.what();
        }
        Environment::terminateEnvironment (env);
    }

};//end of class  demoClob

int main (void)
{
    demoClob *b = new demoClob ();
    b->setUsername ("SCOTT");
    b->setPassword ("TIGER");
    b->runSample ();
}
