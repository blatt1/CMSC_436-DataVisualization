#include <stdlib.h>
#include <iostream>
#include <mysql_connection.h>
#include <driver.h>
#include <exception.h>
#include <resultset.h>
#include <statement.h>
#include <queue>

// #include "encounter.h"

using namespace std;
using namespace sql;

int main(void)
{
  sql::Driver *driver;
  sql::Connection *con;
  Statement *stmt;
  ResultSet *res;

  driver = get_driver_instance();
  con = driver->connect("tcp://192.168.1.6:3306","root","R@ng00n");
  con->setSchema("cohort");
  stmt = con->createStatement();
  res = stmt -> executeQuery ("SELECT des AS symp FROM symptons");
  //retrieve_rsmetadata_and_print(res);

  while (res->next())
  {
    cout << "\t... MySQL replies: ";
    /* Access column data by alias or column name */
    cout << res->getString("symp") << endl;
    cout << "\t... MySQL says it again: ";
    /* Access column data by numeric offset, 1 is the first column */
    cout << res->getString(1) << endl;
  }

  delete res;
  delete stmt;
  con -> close();
  delete con;

  return 0;
}
