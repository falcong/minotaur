// 
//     MINOTAUR -- It's only 1/2 bull
// 
//     (C)opyright 2008 - 2013 The MINOTAUR Team.
// 

/**
 * \file SolutionPool.cpp
 * \brief Define SolutionPool class for a storing solutions.
 * \author Ashutosh Mahajan, Argonne National Laboratory
 */

#include <cmath>

#include "MinotaurConfig.h"
#include "SolutionPool.h"

using namespace Minotaur;

const std::string SolutionPool::me_ = "SolutionPool: ";

SolutionPool::SolutionPool (ProblemPtr problem, UInt limit)
: bestSolution_(SolutionPtr()), // NULL
  numSolsFound_(0),
  problem_(problem),
  sizeLimit_(limit),
  timeFirst_(-1),
  timeLast_(-1)
{
}

void SolutionPool::addSolution(ConstSolutionPtr solution)
{
  // XXX: for now we save only one solution.
  SolutionPtr newsol = (SolutionPtr) new Solution(solution);
  ++numSolsFound_;
  if (sols_.size() > 0) {
    if (sols_[0]->getObjValue() > solution->getObjValue()) {
      sols_[0] = newsol;
      bestSolution_ = newsol;
    }
  } else {
    sols_.push_back(newsol);
    bestSolution_ = newsol;
  }
}


void SolutionPool::addSolution(const Double *x, Double obj_value)
{
  SolutionPtr solution = (SolutionPtr) new Solution(obj_value, x, problem_);
  addSolution(solution);
}


SolutionPtr SolutionPool::getBestSolution()
{
  return bestSolution_;
}


Double SolutionPool::getBestSolutionValue() const
{
  if (bestSolution_) {
    return bestSolution_->getObjValue();
  } else {
    return INFINITY;
  }
}


UInt SolutionPool::getNumSolsFound() const
{
  return numSolsFound_;
}


void SolutionPool::writeStats(std::ostream &out) const
{
  out << me_ << "Number of solutions found = " << numSolsFound_ << std::endl
      << me_ << "Time first solution found = " << timeFirst_    << std::endl
      << me_ << "Time last solution found  = " << timeLast_     << std::endl
      ;
}

// Local Variables: 
// mode: c++ 
// eval: (c-set-style "k&r") 
// eval: (c-set-offset 'innamespace 0) 
// eval: (setq c-basic-offset 2) 
// eval: (setq fill-column 78) 
// eval: (auto-fill-mode 1) 
// eval: (setq column-number-mode 1) 
// eval: (setq indent-tabs-mode nil) 
// End:
