// Gmsh - Copyright (C) 1997-2008 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to <gmsh@geuz.org>.

#ifndef _CUT_GRID_H_
#define _CUT_GRID_H_

#include "Plugin.h"

extern "C"
{
  GMSH_Plugin *GMSH_RegisterCutGridPlugin ();
}

class GMSH_CutGridPlugin : public GMSH_Post_Plugin
{
  static double callback(int num, int action, double value, double *opt,
                         double step, double min, double max);
  void addInView(int numsteps, int connect, int nbcomp, 
                 double ***pnts, double ***vals, 
                 List_T *P, int *nP, 
                 List_T *L, int *nL, 
                 List_T *Q, int *nQ);
  PView *GenerateView (PView *v, int connectPoints);
public:
  GMSH_CutGridPlugin(){}
  void getName(char *name) const;
  void getInfos(char *author, char *copyright, char *help_text) const;
  void catchErrorMessage(char *errorMessage) const;
  int getNbOptions() const;
  StringXNumber *getOption(int iopt);  
  PView *execute(PView *);

  static int getNbU ();
  static int getNbV ();
  static void getPoint(int iU, int iV, double *X );

  static double callbackX0(int, int, double);
  static double callbackY0(int, int, double);
  static double callbackZ0(int, int, double);
  static double callbackX1(int, int, double);
  static double callbackY1(int, int, double);
  static double callbackZ1(int, int, double);
  static double callbackX2(int, int, double);
  static double callbackY2(int, int, double);
  static double callbackZ2(int, int, double);
  static double callbackU(int, int, double);
  static double callbackV(int, int, double);
  static double callbackConnect(int, int, double);
  static void draw(void *context);
};

#endif
