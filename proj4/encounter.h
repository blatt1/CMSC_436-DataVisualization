#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include <string>

using namespace std;

class Encounter
{
  public:         
    Encounter(int pid, string symp, int days);

    int    get_pid();
    string get_symp();
    int    get_days();

  private:
    int pid;
    string symp;
    int days;
};

#endif
