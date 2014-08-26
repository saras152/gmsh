// Gmsh - Copyright (C) 1997-2013 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to the public mailing list <gmsh@geuz.org>.

#ifndef _METRIC_BASIS_H_
#define _METRIC_BASIS_H_

#include "MElement.h"
#include "JacobianBasis.h"
#include "fullMatrix.h"
#include <fstream>
#include <cmath>

class MetricBasis {
  friend class MetricCoefficient;
  friend class GMSH_AnalyseCurvedMeshPlugin;
private:
  const JacobianBasis *_jacobian;
  const GradientBasis *_gradients;
  const bezierBasis *_bezier;
  static double _tol;

  std::fstream file;

  class IneqData {
  public:
    int i, j, k;
    double val;

  public:
    IneqData(double val, int i, int j, int k = -1) : i(i), j(j), k(k), val(val) {}
  };

  class MetricData {
   public:
    fullMatrix<double> *_metcoeffs;
    fullVector<double> *_jaccoeffs;
    double _RminBez;
    int _depth, _num;

   public:
    MetricData(fullMatrix<double> *m, fullVector<double> *j, double r, int d, int num) :
      _metcoeffs(m), _jaccoeffs(j), _RminBez(r), _depth(d), _num(num) {}
    ~MetricData() {
      delete _metcoeffs;
      delete _jaccoeffs;
    }
  };

  std::map<int, std::vector<IneqData> > _ineqJ2, _ineqP3, _ineqA;

public:
  MetricBasis(int elementTag);

  static void setTol(double tol) {_tol = tol;}
  static double boundMinR(MElement *el);
  static double minRCorner(MElement *el);
  static double minSampledR(MElement *el, int order);

  double getBoundMinR(MElement*);
  double getMinSampledR(MElement*, int) const;

  void interpolate(const MElement*, const MetricData*, const double *uvw, double *minmaxQ) const;

  static int metricOrder(int tag);

private:
  void _fillInequalities(int order);
  void _lightenInequalities(int&, int&, int&); //TODO change

  void _computeRmin(const fullMatrix<double>&, const fullVector<double>&,
                    double &RminLag, double &RminBez) const;
  void _computeRmax(const fullMatrix<double>&, const fullVector<double>&,
                    double &RmaxLag) const;
  void _computeTermBeta(double &a, double &K, double &dRda,
                        double &term1, double &phip) const;
  void _getMetricData(MElement*, MetricData*&) const;

  double _subdivideForRmin(MetricData*, double RminLag, double tol) const;
  static void _fillCoeff(const GradientBasis*,
                  fullMatrix<double> &nodes, fullMatrix<double> &coeff);
  static double _computeMinlagR(const fullVector<double> &jac,
                                const fullMatrix<double> &coeff, int num);

  static int _paramOnPlane(const fullMatrix<double> &nodes3d,
                           fullMatrix<double> &nodes2d);

  void _minMaxA(const fullMatrix<double>&, double &min, double &max) const;
  void _minK(const fullMatrix<double>&, const fullVector<double>&, double &min) const;
  void _maxAstKpos(const fullMatrix<double>&, const fullVector<double>&,
                 double minK, double beta, double &maxa) const;
  void _maxAstKneg(const fullMatrix<double>&, const fullVector<double>&,
                 double minK, double beta, double &maxa) const;
  void _maxKstAfast(const fullMatrix<double>&, const fullVector<double>&,
                 double mina, double beta, double &maxK) const;
  void _maxKstAsharp(const fullMatrix<double>&, const fullVector<double>&,
                 double mina, double beta, double &maxK) const;

  static double _R3Dsafe(double a, double K) {
    const double x = .5 * (K - a*a*a + 3*a);
    if (x > 1+1e-13 || x < -1-1e-13) {
      Msg::Warning("x = %g (|1+%g|)", x, std::abs(x)-1);
    }

    double ans;
    if (x >= 1)       ans = (a - 1) / (a + 2);
    else if (x <= -1) ans = (a - 2) / (a + 1);
    else {
      const double phi = std::acos(x) / 3;
      ans = (a + 2*std::cos(phi + 2*M_PI/3)) / (a + 2*std::cos(phi));
    }

    if (ans < 0 || ans > 1) {
      Msg::Warning("R = %g", ans);
      if (ans < 0) return 0;
      else return 1;
    }
    return ans;
  }
  static double _R2Dsafe(double a) {
    if (a < 1) Msg::Warning("R2d = %g", (a - 1) / (a + 1));
    return (a - 1) / (a + 1);
  }

private:
  class gterIneq {
   public:
    bool operator()(const IneqData &id1, const IneqData &id2) const {
      return id1.val > id2.val;
    }
  };
  struct lessMinB {
    bool operator()(const MetricData *md1, const MetricData *md2) const {
      return md1->_RminBez > md2->_RminBez;
    }
  };
};

#endif
