/**
 *occicoll - To exhibit simple insert, delete & update operations"
 *     " on table having a Nested Table column
 *
 *Description
 *  Create a program which has insert,delete and update on a
 *  table having a Nested table column.
 *  Perform all these operations using OCCI interface.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <string.h>
#include <occi.h>
using namespace oracle::occi;
using namespace std;

typedef vector<string> journal;

class occicoll
{
private:

    Environment *env;
    Connection *conn;
    Statement *stmt;
    string tableName;
    string typeName;

public:

    occicoll (string user, string passwd, string db)
    {
        env = Environment::createEnvironment (Environment::OBJECT);
        conn = env->createConnection (user, passwd, db);
        initRows();
    }

    ~occicoll ()
    {
        env->terminateConnection (conn);
        Environment::terminateEnvironment (env);
    }

    void setTableName (string s)
    {
        tableName = s;
    }

    void initRows ()
    {
        try{
            Statement *st1 = conn->createStatement ("DELETE FROM journal_tab");
            st1->executeUpdate ();
            st1->setSQL("INSERT INTO journal_tab (jid, jname) VALUES (22, journal ('NATION', 'TIMES'))");
            st1->executeUpdate ();
            st1->setSQL("INSERT INTO journal_tab (jid, jname) VALUES (33, journal ('CRICKET', 'ALIVE'))");
            st1->executeUpdate ();
            conn->commit();
            conn->terminateStatement (stmt);
        }catch(SQLException ex)
        {
            cout<<ex.what();
        }
    }
    /**
     * Insertion of a row 
     */
    void insertRow ()
    {
        int c1 = 11;
        journal c2;

        c2.push_back ("LIFE");
        c2.push_back ("TODAY");
        c2.push_back ("INVESTOR");

        cout << "Inserting row with jid = " << 11 << 
            " and journal_tab (LIFE, TODAY, INVESTOR )" << endl;
        try{
            stmt = conn->createStatement (
                    "INSERT INTO journal_tab (jid, jname) VALUES (:x, :y)");
            stmt->setInt (1, c1);
            setVector (stmt, 2, c2, "JOURNAL");
            stmt->executeUpdate ();
        }catch(SQLException ex)
        {
            cout<<"Exception thrown for insertRow"<<endl;
            cout<<"Error number: "<<  ex.getErrorCode() << endl;
            cout<<ex.getMessage() << endl;
        }
        cout << "Insertion - Successful" << endl;
        conn->terminateStatement (stmt);

    }

    // Displaying all the rows of the table
    void displayAllRows ()
    {
        cout << "Displaying all the rows of the table" << endl;
        stmt = conn->createStatement (
                "SELECT jid, jname FROM journal_tab");

        journal c2;

        ResultSet *rs = stmt->executeQuery();
        try{
            while (rs->next())
            {
                cout << "jid: " << rs->getInt(1) << endl;
                cout << "jname: ";
                getVector (rs, 2, c2);
                for (int i = 0; i < c2.size(); ++i)
                    cout << c2[i] << " ";
                cout << endl;
            }
        }catch(SQLException ex)
        {
            cout<<"Exception thrown for displayRow"<<endl;
            cout<<"Error number: "<<  ex.getErrorCode() << endl;
            cout<<ex.getMessage() << endl;
        }
        stmt->closeResultSet (rs);
        conn->terminateStatement (stmt);

    } // End of displayAllRows()

    // Deleting a row in a nested table  
    void deleteRow (int c1, string str)
    {
        cout << "Deleting a row in a nested table of strings" << endl;
        stmt = conn->createStatement (
                "SELECT jname FROM journal_tab WHERE jid = :x");
        journal c2;
        stmt->setInt (1, c1);

        ResultSet *rs = stmt->executeQuery();
        try{
            if (rs->next())
            {
                getVector (rs, 1, c2);
                c2.erase (find (c2.begin(), c2.end(), str)); 
            }
            stmt->setSQL ("UPDATE journal_tab SET jname = :x WHERE jid = :y");
            stmt->setInt (2, c1);
            setVector (stmt, 1, c2, "JOURNAL");
            stmt->executeUpdate ();
        }catch(SQLException ex)
        {
            cout<<"Exception thrown for delete row"<<endl;
            cout<<"Error number: "<<  ex.getErrorCode() << endl;
            cout<<ex.getMessage() << endl;
        }

        cout << "Deletion - Successful" << endl;
        conn->commit();
        stmt->closeResultSet (rs);
        conn->terminateStatement (stmt);
    } // End of deleteRow (int, string)

    // Updating a row of the nested table of strings
    void updateRow (int c1, string str)
    {
        cout << "Updating a row of the nested table of strings" << endl;
        stmt = conn->createStatement (
                "SELECT jname FROM journal_tab WHERE jid = :x");

        journal c2;

        stmt->setInt (1, c1);
        ResultSet *rs = stmt->executeQuery();
        try{
            if (rs->next())
            {
                getVector (rs, 1, c2);
                c2[0] = str;
            }
            stmt->setSQL ("UPDATE journal_tab SET jname = :x WHERE jid = :y");
            stmt->setInt (2, c1);
            setVector (stmt, 1, c2, "JOURNAL");
            stmt->executeUpdate ();
        }catch(SQLException ex)
        {
            cout<<"Exception thrown for updateRow"<<endl;
            cout<<"Error number: "<<  ex.getErrorCode() << endl;
            cout<<ex.getMessage() << endl;
        }

        cout << "Updation - Successful" << endl;
        conn->commit();
        stmt->closeResultSet (rs);
        conn->terminateStatement (stmt);
    } // End of UpdateRow (int, string)

};//end of class occicoll

int main (void)
{
    string user = "SCOTT";
    string passwd = "TIGER";
    string db = "";

    try
    {
        cout << "occicoll - Exhibiting simple insert, delete & update operations" 
            " on table having a Nested Table column" << endl;
        occicoll *demo = new occicoll (user, passwd, db);

        cout << "Displaying all rows before the operations" << endl;
        demo->displayAllRows ();

        demo->insertRow ();

        demo->deleteRow (11, "TODAY");

        demo->updateRow (33, "New_String");

        cout << "Displaying all rows after all the operations" << endl;
        demo->displayAllRows ();

        delete (demo);
        cout << "occicoll - done" << endl;
    }catch (SQLException ea)
    {
        cerr << "Error running the demo: " << ea.getMessage () << endl;
    }
}

