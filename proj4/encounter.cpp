#include "encounter.h"

Encounter::Encounter(int pid, string symp, int days)
{
  this->pid  = pid;
  this->symp = symp;
  this->days = days;
}

int Encounter::get_pid()
{
  return this->pid;
}

string Encounter::get_symp()
{
  return this->symp;
}

int Encounter::get_days()
{
  return this->days;
}
