/**
 * occidml - To exhibit the insertion, Selection, updating and deletion of 
 *            a row through OCCI.
 *
 * Description
 *   Create a program which has insert, select, update & delete as operations. 
 *   Perform all these operations using OCCI interface.
 */

#include <iostream>
#include <occi.h>
using namespace oracle::occi;
using namespace std;

class  occidml
{
private:

    Environment *env;
    Connection *conn;
    Statement *stmt;
public:

    occidml (string user, string passwd, string db)
    {
        env = Environment::createEnvironment (Environment::DEFAULT);
        conn = env->createConnection (user, passwd, db);
    }

    ~occidml ()
    {
        env->terminateConnection (conn);
        Environment::terminateEnvironment (env);
    }

    /**
     * Insertion of a row with dynamic binding, PreparedStatement functionality.
     */
    void insertBind (int c1, string c2)
    {
        string sqlStmt = "INSERT INTO author_tab VALUES (:x, :y)";
        stmt=conn->createStatement (sqlStmt);
        try{
            stmt->setInt (1, c1);
            stmt->setString (2, c2);
            stmt->executeUpdate ();
            cout << "insert - Success" << endl;
        }catch(SQLException ex)
        {
            cout<<"Exception thrown for insertBind"<<endl;
            cout<<"Error number: "<<  ex.getErrorCode() << endl;
            cout<<ex.getMessage() << endl;
        }

        conn->terminateStatement (stmt);
    }

    /**
     * Inserting a row into the table.
     */
    void insertRow ()
    {
        string sqlStmt = "INSERT INTO author_tab VALUES (111, 'ASHOK')";
        stmt = conn->createStatement (sqlStmt);
        try{
            stmt->executeUpdate ();
            cout << "insert - Success" << endl;
        }catch(SQLException ex)
        {
            cout<<"Exception thrown for insertRow"<<endl;
            cout<<"Error number: "<<  ex.getErrorCode() << endl;
            cout<<ex.getMessage() << endl;
        }

        conn->terminateStatement (stmt);
    }

    /**
     * updating a row
     */
    void updateRow (int c1, string c2)
    {
        string sqlStmt = 
            "UPDATE author_tab SET author_name = :x WHERE author_id = :y";
        stmt = conn->createStatement (sqlStmt);
        try{
            stmt->setString (1, c2);
            stmt->setInt (2, c1);
            stmt->executeUpdate ();
            cout << "update - Success" << endl;
        }catch(SQLException ex)
        {
            cout<<"Exception thrown for updateRow"<<endl;
            cout<<"Error number: "<<  ex.getErrorCode() << endl;
            cout<<ex.getMessage() << endl;
        }

        conn->terminateStatement (stmt);
    }


    /**
     * deletion of a row
     */
    void deleteRow (int c1, string c2)
    {
        string sqlStmt = 
            "DELETE FROM author_tab WHERE author_id= :x AND author_name = :y";
        stmt = conn->createStatement (sqlStmt);
        try{
            stmt->setInt (1, c1);
            stmt->setString (2, c2);
            stmt->executeUpdate ();
            cout << "delete - Success" << endl;
        }catch(SQLException ex)
        {
            cout<<"Exception thrown for deleteRow"<<endl;
            cout<<"Error number: "<<  ex.getErrorCode() << endl;
            cout<<ex.getMessage() << endl;
        }

        conn->terminateStatement (stmt);
    }

    /**
     * displaying all the rows in the table
     */
    void displayAllRows ()
    {
        string sqlStmt = "SELECT author_id, author_name FROM author_tab";
        stmt = conn->createStatement (sqlStmt);
        ResultSet *rset = stmt->executeQuery ();
        try{
            while (rset->next ())
            {
                cout << "author_id: " << rset->getInt (1) << "  author_name: " 
                    << rset->getString (2) << endl;
            }
        }catch(SQLException ex)
        {
            cout<<"Exception thrown for displayAllRows"<<endl;
            cout<<"Error number: "<<  ex.getErrorCode() << endl;
            cout<<ex.getMessage() << endl;
        }

        stmt->closeResultSet (rset);
        conn->terminateStatement (stmt);
    }

}; // end of class  occidml


int main (void)
{
    string user = "SCOTT";
    string passwd = "TIGER";
    string db = "";

    cout << "occidml - Exhibiting simple insert, delete & update operations" 
        << endl;
    occidml *demo = new occidml (user, passwd, db);

    cout << "Displaying all records before any operation" << endl;
    demo->displayAllRows ();

    cout << "Inserting a record into the table author_tab " 
        << endl;
    demo->insertRow ();

    cout << "Displaying the records after insert " << endl;
    demo->displayAllRows ();

    cout << "Inserting a records into the table author_tab using dynamic bind"
        << endl;
    demo->insertBind (222, "ANAND");

    cout << "Displaying the records after insert using dynamic bind" << endl;
    demo->displayAllRows ();

    cout << "deleting a row with author_id as 222 from author_tab table" << endl;
    demo->deleteRow (222, "ANAND");

    cout << "updating a row with author_id as 444 from author_tab table" << endl;
    demo->updateRow (444, "ADAM");

    cout << "displaying all rows after all the operations" << endl;
    demo->displayAllRows ();

    delete (demo);
    cout << "occidml - done" << endl;
}

