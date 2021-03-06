#pragma once
#if ROOT_VERSION_CODE >= ROOT_VERSION(6, 00, 0)
#include <TMath.h>
#include <fun4all/Fun4AllServer.h>
#include <g4detectors/PHG4CylinderSubsystem.h>
#include <g4eval/SvtxEvaluator.h>
#include <g4main/PHG4Reco.h>
#include <g4mvtx/PHG4MvtxDefs.h>
#include <g4mvtx/PHG4MvtxSubsystem.h>
#include <g4tpc/PHG4TpcSpaceChargeDistortion.h>
#include "GlobalVariables.C"
R__LOAD_LIBRARY(libg4eval.so)
R__LOAD_LIBRARY(libg4mvtx.so)
#endif

#include <vector>

// ONLY if backward compatibility with hits files already generated with 8 inner TPC layers is needed, you can set this to "true"
bool tpc_layers_40 = false;

// if true, refit tracks with primary vertex included in track fit  - good for analysis of prompt tracks only
// Adds second node to node tree, keeps original track node undisturbed
// Adds second evaluator to process refitted tracks and outputs separate ntuples
bool use_primary_vertex = false;

const int n_maps_layer = 3;  // must be 0-3, setting it to zero removes Mvtx completely, n < 3 gives the first n layers

// default setup for the INTT - please don't change this. The configuration can be redone later in the nacro if desired
int n_intt_layer = 0;
// default layer configuration
int laddertype[4] = {0, 1, 1, 1};                                // default
int nladder[4] = {34, 30, 36, 42};                               // default
double sensor_radius_inner[4] = {6.876, 8.987, 10.835, 12.676};  // inner staggered radius for layer default
double sensor_radius_outer[4] = {7.462, 9.545, 11.361, 13.179};  // outer staggered radius for layer  default

int n_tpc_layer_inner = 16;
double tpc_layer_thick_inner = 1.25;  // EIC- recover default inner radius of TPC vol.
int tpc_layer_rphi_count_inner = 1152;

int n_tpc_layer_mid = 16;
double tpc_layer_thick_mid = 1.25;
int tpc_layer_rphi_count_mid = 1536;

int n_tpc_layer_outer = 16;
double tpc_layer_thick_outer = 1.125;  // outer later reach from 60-78 cm (instead of 80 cm), that leads to radial thickness of 1.125 cm
int tpc_layer_rphi_count_outer = 2304;

int n_gas_layer = n_tpc_layer_inner + n_tpc_layer_mid + n_tpc_layer_outer;

double inner_cage_radius = 20.;
double inner_readout_radius = 30.;

// TPC gas parameters
// These are set for a variety of gas choices...
//==============================================
enum TPC_Gas
{
  Ne2K_100,
  Ne2K_400,
  NeCF4_100,
  NeCF4_300,
  NeCF4_400,
  ByHand
};
TPC_Gas ether = TPC_Gas::NeCF4_400;
//TPC_Gas ether = TPC_Gas::ByHand;

// Data on gasses @20 C and 760 Torr from the following source:
// http://www.slac.stanford.edu/pubs/icfa/summer98/paper3/paper3.pdf
double Ne_dEdx = 1.56;    // keV/cm
double CF4_dEdx = 7.00;   // keV/cm
double iBut_dEdx = 5.93;  // keV/cm

double Ne_NPrimary = 12;    // Number/cm
double CF4_NPrimary = 51;   // Number/cm
double iBut_NPrimary = 84;  // Number/cm

double Ne_NTotal = 43;     // Number/cm
double CF4_NTotal = 100;   // Number/cm
double iBut_NTotal = 195;  // Number/cm

// TPC Performance Parameter (applies extra smear to mimic the avalanche):
double TPC_SigmaT = 0.03;  // 0.03 means 300 microns...Prakhar Garg Simulation...desire measurement...

// to be overwritten...
double TPCDriftVelocity;
double TPC_Trans_Diffusion;
double TPC_Long_Diffusion;
double TPC_dEdx;
double TPC_NPri;
double TPC_NTot;
double TPC_ElectronsPerKeV;

// TPC readout shaping time and ADC clock parameters
// these set the Z size of the TPC cells
// These need to be set in the init since some of them require the drift velocity...
//=======================================
double TPCADCClock;
double TPCShapingRMSLead;
double TPCShapingRMSTail;
double tpc_cell_z;
double TPC_SmearRPhi;
double TPC_SmearZ;

int Max_si_layer;

void SvtxInit(int verbosity = 0)
{
  Max_si_layer = n_maps_layer + n_intt_layer + n_gas_layer;

  switch (ether)
  {
  // https://www.phenix.bnl.gov/WWW/p/draft/prakhar/tpc/HTML_Gas_Linear/Ne_CF4_IC4H10_95_3_2.html
  case TPC_Gas::Ne2K_100:
  {
    if (verbosity)
      cout << "Gas Choice:  TPC_Gas::Ne2K_100" << endl;
    TPCDriftVelocity = 3.2 / 1000.0;  // cm/ns
    TPC_Trans_Diffusion = 0.0065;     // cm/SQRT(cm)
    TPC_Long_Diffusion = 0.0300;      // cm/SQRT(cm)
    TPC_dEdx = 0.95 * Ne_dEdx + 0.03 * CF4_dEdx + 0.02 * iBut_dEdx;
    TPC_NPri = 0.95 * Ne_NPrimary + 0.03 * CF4_NPrimary + 0.02 * iBut_NPrimary;
    TPC_NTot = 0.95 * Ne_NTotal + 0.03 * CF4_NTotal + 0.02 * iBut_NTotal;
    break;
  }
  case TPC_Gas::Ne2K_400:
  {
    if (verbosity)
      cout << "Gas Choice:  TPC_Gas::Ne2K_400" << endl;
    TPCDriftVelocity = 5.5 / 1000.0;  // cm/ns
    TPC_Trans_Diffusion = 0.0120;     // cm/SQRT(cm)
    TPC_Long_Diffusion = 0.0175;      // cm/SQRT(cm)
    TPC_dEdx = 0.95 * Ne_dEdx + 0.03 * CF4_dEdx + 0.02 * iBut_dEdx;
    TPC_NPri = 0.95 * Ne_NPrimary + 0.03 * CF4_NPrimary + 0.02 * iBut_NPrimary;
    TPC_NTot = 0.95 * Ne_NTotal + 0.03 * CF4_NTotal + 0.02 * iBut_NTotal;
    break;
  }
  // https://www.phenix.bnl.gov/WWW/p/draft/prakhar/tpc/HTML_Gas_Linear/Ne_CF4_90_10.html
  case TPC_Gas::NeCF4_100:
  {
    if (verbosity)
      cout << "Gas Choice:  TPC_Gas::NeCF4_100" << endl;
    TPCDriftVelocity = 4.0 / 1000.0;  // cm/ns
    TPC_Trans_Diffusion = 0.0045;     // cm/SQRT(cm)
    TPC_Long_Diffusion = 0.0270;      // cm/SQRT(cm)
    TPC_dEdx = 0.90 * Ne_dEdx + 0.10 * CF4_dEdx;
    TPC_NPri = 0.90 * Ne_NPrimary + 0.10 * CF4_NPrimary;
    TPC_NTot = 0.90 * Ne_NTotal + 0.10 * CF4_NTotal;
    break;
  }
  case TPC_Gas::NeCF4_300:
  {
    if (verbosity)
      cout << "Gas Choice:  TPC_Gas::NeCF4_300" << endl;
    TPCDriftVelocity = 7.0 / 1000.0;  // cm/ns
    TPC_Trans_Diffusion = 0.0052;     // cm/SQRT(cm)
    TPC_Long_Diffusion = 0.0170;      // cm/SQRT(cm)
    TPC_dEdx = 0.90 * Ne_dEdx + 0.10 * CF4_dEdx;
    TPC_NPri = 0.90 * Ne_NPrimary + 0.10 * CF4_NPrimary;
    TPC_NTot = 0.90 * Ne_NTotal + 0.10 * CF4_NTotal;
    break;
  }
  case TPC_Gas::NeCF4_400:
  {
    if (verbosity)
      cout << "Gas Choice:  TPC_Gas::NeCF4_400" << endl;
    TPCDriftVelocity = 8.0 / 1000.0;  // cm/ns
    TPC_Trans_Diffusion = 0.0060;     // cm/SQRT(cm)
    TPC_Long_Diffusion = 0.0150;      // cm/SQRT(cm)
    TPC_dEdx = 0.90 * Ne_dEdx + 0.10 * CF4_dEdx;
    TPC_NPri = 0.90 * Ne_NPrimary + 0.10 * CF4_NPrimary;
    TPC_NTot = 0.90 * Ne_NTotal + 0.10 * CF4_NTotal;
    break;
  }
  case TPC_Gas::ByHand:
  {
    if (verbosity)
      cout << "Gas Choice:  TPC_Gas::ByHand" << endl;
    TPCDriftVelocity = 6.0 / 1000.0;  // cm/ns
    TPC_Trans_Diffusion = 0.0130;     // cm/SQRT(cm)
    TPC_Long_Diffusion = 0.0130;      // cm/SQRT(cm)
    TPC_ElectronsPerKeV = 28.0;
    TPC_dEdx = 0.90 * Ne_dEdx + 0.10 * CF4_dEdx;
    TPC_NPri = 0.90 * Ne_NPrimary + 0.10 * CF4_NPrimary;
    TPC_NTot = TPC_ElectronsPerKeV * TPC_dEdx;
    break;
  }
  default:  // defaults to NeCF4_400
  {
    if (verbosity)
      cout << "Gas Choice Undefined...using TPC_Gas::NeCF4_400" << endl;
    TPCDriftVelocity = 8.0 / 1000.0;  // cm/ns
    TPC_Trans_Diffusion = 0.0060;     // cm/SQRT(cm)
    TPC_Long_Diffusion = 0.0150;      // cm/SQRT(cm)
    TPC_dEdx = 0.90 * Ne_dEdx + 0.10 * CF4_dEdx;
    TPC_NPri = 0.90 * Ne_NPrimary + 0.10 * CF4_NPrimary;
    TPC_NTot = 0.90 * Ne_NTotal + 0.10 * CF4_NTotal;
    break;
  }
  }

  TPC_ElectronsPerKeV = TPC_NTot / TPC_dEdx;

  // TPC readout shaping time and ADC clock parameters
  // these set the Z size of the TPC cells
  //=======================================
  TPCShapingRMSLead = 32.0;                     // ns, rising RMS equivalent of shaping amplifier for 80 ns SAMPA
  TPCShapingRMSTail = 48.0;                     // ns, falling RMS equivalent of shaping amplifier for 80 ns SAMPA
  TPCADCClock = 53.0;                           // ns, corresponds to an ADC clock rate of 18.8 MHz
  tpc_cell_z = TPCADCClock * TPCDriftVelocity;  // cm

  //  these are fudge parameters, tuned to give average of 150 microns r-phi and 500 microns Z resolution in the outer TPC layers with the TPC setup used here and 80 ns SAMPA peaking time
  TPC_SmearRPhi = 0.25;
  TPC_SmearZ = 0.15;
}

double Svtx(PHG4Reco* g4Reco, double radius,
            const int absorberactive = 0,
            int verbosity = 0)
{
  gSystem->Load("libg4mvtx.so");
  if (n_maps_layer > 0)
  {
    bool maps_overlapcheck = false;  // set to true if you want to check for overlaps

    // Update EIC MAPS layer structure based on inner two layers of U. Birmingham tracker

    PHG4MvtxSubsystem* mvtx = new PHG4MvtxSubsystem("MVTX");
    mvtx->Verbosity(verbosity);

    // H?kan Wennl?f <hwennlof@kth.se> :
    //    Without time-stamping layer:
    //    Stave type  Length  Overlap Radius [mm] Tilt  Radiation length  Number of staves
    //    ALICE inner 270 mm  2 mm  36.4  12.0 deg  0.3 % X0  18
    //    ALICE inner 270 mm  2 mm  59.8  12.0 deg  0.3 % X0  30
    //    ALICE outer 840 mm  4 mm  133.8 6.0 deg 0.8 % X0  16
    //    ALICE outer 840 mm  4 mm  180 6.0 deg 0.8 % X0  21


    static const double Degree2Rad = 180. / TMath::Pi();
    int ilyr = 0;
    mvtx->set_int_param(ilyr, "active", 1);  //non-automatic initialization in PHG4DetectorGroupSubsystem
    mvtx->set_int_param(ilyr, "layer", ilyr);
    mvtx->set_int_param(ilyr, "N_staves", 18);
    mvtx->set_double_param(ilyr, "layer_nominal_radius", 36.4); // mm
    mvtx->set_double_param(ilyr, "phitilt", 12.0 * Degree2Rad + TMath::Pi());
    mvtx->set_double_param(ilyr, "phi0", 0);

    // Then add a new mid layer that is extrapolation of the inner two.
    ++ilyr;
    mvtx->set_int_param(ilyr, "active", 1);  //non-automatic initialization in PHG4DetectorGroupSubsystem
    mvtx->set_int_param(ilyr, "layer", ilyr);
    mvtx->set_int_param(ilyr, "N_staves", 24);
    mvtx->set_double_param(ilyr, "layer_nominal_radius", 48.1 ); // mm
    mvtx->set_double_param(ilyr, "phitilt", 12.0 * Degree2Rad + TMath::Pi());
    mvtx->set_double_param(ilyr, "phi0", 0);

    ++ilyr;
    mvtx->set_int_param(ilyr, "active", 1);  //non-automatic initialization in PHG4DetectorGroupSubsystem
    mvtx->set_int_param(ilyr, "layer", ilyr);
    mvtx->set_int_param(ilyr, "N_staves", 30);
    mvtx->set_double_param(ilyr, "layer_nominal_radius", 59.8 ); // mm
    mvtx->set_double_param(ilyr, "phitilt", 12.0 * Degree2Rad + TMath::Pi());
    mvtx->set_double_param(ilyr, "phi0", 0);

//    // Then add a new 3rd layer that is extrapolation of the inner two.
//    ++ilyr;
//    mvtx->set_int_param(ilyr, "active", 1);  //non-automatic initialization in PHG4DetectorGroupSubsystem
//    mvtx->set_int_param(ilyr, "layer", ilyr);
//    mvtx->set_int_param(ilyr, "N_staves", 42);
//    mvtx->set_double_param(ilyr, "layer_nominal_radius", 83.2 ); // mm
//    mvtx->set_double_param(ilyr, "phitilt", 12.0 * Degree2Rad + TMath::Pi());
//    mvtx->set_double_param(ilyr, "phi0", 0);

    mvtx->set_string_param(PHG4MvtxDefs::GLOBAL, "stave_geometry_file", string(getenv("CALIBRATIONROOT")) + string("/Tracking/geometry/mvtx_stave_v1.gdml"));
    mvtx->SetActive(1);
    mvtx->OverlapCheck(maps_overlapcheck);
    g4Reco->registerSubsystem(mvtx);
  }  //   if (n_maps_layer > 0)

  assert(n_intt_layer == 0);

  //  int verbosity = 1;

  // time projection chamber layers --------------------------------------------

  // switch ONLY for backward compatibility with 40 layer hits files!
  if (tpc_layers_40)
  {
    n_tpc_layer_inner = 8;
    tpc_layer_thick_inner = 1.25;
    tpc_layer_rphi_count_inner = 1152;
    cout << "Using 8 inner_layers for backward comatibility" << endl;
  }

  PHG4CylinderSubsystem* cyl;

  radius = inner_cage_radius;

  double cage_length = 211.0;  // From TPC group, gives eta = 1.1 at 78 cm
  double n_rad_length_cage = 1.13e-02;
  double cage_thickness = 28.6 * n_rad_length_cage;  // Kapton X_0 = 28.6 cm  // mocks up Kapton + carbon fiber structure
  
	bool istpc = false;

  // inner field cage
  /**/
	if(0){
	if (istpc){
  cyl = new PHG4CylinderSubsystem("SVTXSUPPORT", n_maps_layer + n_intt_layer);
  cyl->set_double_param("radius", radius);
  cyl->set_int_param("lengthviarapidity", 0);
  cyl->set_double_param("length", cage_length);
  cyl->set_string_param("material", "G4_KAPTON");
  cyl->set_double_param("thickness", cage_thickness);
  cyl->SuperDetector("SVTXSUPPORT");
  cyl->Verbosity(0);
  g4Reco->registerSubsystem(cyl);

  radius += cage_thickness;

  double inner_readout_radius = radius;
  //  if (inner_readout_radius < radius) inner_readout_radius = radius;
  //
  string tpcgas = "sPHENIX_TPC_Gas";  //  Ne(90%) CF4(10%) - defined in g4main/PHG4Reco.cc
                                      //
                                      //  // Layer of inert TPC gas from 20-30 cm
                                      //  if (inner_readout_radius - radius > 0)
                                      //  {
                                      //    cyl = new PHG4CylinderSubsystem("SVTXSUPPORT", n_maps_layer + n_intt_layer + 1);
                                      //    cyl->set_double_param("radius", radius);
                                      //    cyl->set_int_param("lengthviarapidity", 0);
                                      //    cyl->set_double_param("length", cage_length);
                                      //    cyl->set_string_param("material", tpcgas.c_str());
                                      //    cyl->set_double_param("thickness", inner_readout_radius - radius);
                                      //    cyl->SuperDetector("SVTXSUPPORT");
                                      //    g4Reco->registerSubsystem(cyl);
                                      //  }
                                      //
                                      //  radius = inner_readout_radius;

  double outer_radius = 78.;

  // Active layers of the TPC from 30-40 cm (inner layers)

  for (int ilayer = n_maps_layer + n_intt_layer; ilayer < (n_maps_layer + n_intt_layer + n_tpc_layer_inner); ++ilayer)
  {
    if (verbosity)
      cout << "Create TPC gas layer " << ilayer << " with inner radius " << radius << " cm "
           << " thickness " << tpc_layer_thick_inner - 0.01 << " length " << cage_length << endl;

    cyl = new PHG4CylinderSubsystem("SVTX", ilayer);
    cyl->set_double_param("radius", radius);
    cyl->set_int_param("lengthviarapidity", 0);
    cyl->set_double_param("length", cage_length);
    cyl->set_string_param("material", tpcgas.c_str());
    cyl->set_double_param("thickness", tpc_layer_thick_inner - 0.01);
    cyl->SetActive();
    cyl->SuperDetector("SVTX");
    g4Reco->registerSubsystem(cyl);

    radius += tpc_layer_thick_inner;
  }

  // Active layers of the TPC from 40-60 cm (mid layers)

  for (int ilayer = n_maps_layer + n_intt_layer + n_tpc_layer_inner; ilayer < (n_maps_layer + n_intt_layer + n_tpc_layer_inner + n_tpc_layer_mid); ++ilayer)
  {
    if (verbosity)
      cout << "Create TPC gas layer " << ilayer << " with inner radius " << radius << " cm "
           << " thickness " << tpc_layer_thick_mid - 0.01 << " length " << cage_length << endl;

    cyl = new PHG4CylinderSubsystem("SVTX", ilayer);
    cyl->set_double_param("radius", radius);
    cyl->set_int_param("lengthviarapidity", 0);
    cyl->set_double_param("length", cage_length);
    cyl->set_string_param("material", tpcgas.c_str());
    cyl->set_double_param("thickness", tpc_layer_thick_mid - 0.01);
    cyl->SetActive();
    cyl->SuperDetector("SVTX");
    g4Reco->registerSubsystem(cyl);

    radius += tpc_layer_thick_mid;
  }

  // Active layers of the TPC from 60-80 cm (outer layers)

  for (int ilayer = n_maps_layer + n_intt_layer + n_tpc_layer_inner + n_tpc_layer_mid; ilayer < (n_maps_layer + n_intt_layer + n_tpc_layer_inner + n_tpc_layer_mid + n_tpc_layer_outer); ++ilayer)
  {
    if (verbosity)
      cout << "Create TPC gas layer " << ilayer << " with inner radius " << radius << " cm "
           << " thickness " << tpc_layer_thick_outer - 0.01 << " length " << cage_length << endl;

    cyl = new PHG4CylinderSubsystem("SVTX", ilayer);
    cyl->set_double_param("radius", radius);
    cyl->set_int_param("lengthviarapidity", 0);
    cyl->set_double_param("length", cage_length);
    cyl->set_string_param("material", tpcgas.c_str());
    cyl->set_double_param("thickness", tpc_layer_thick_outer - 0.01);
    cyl->SetActive();
    cyl->SuperDetector("SVTX");
    g4Reco->registerSubsystem(cyl);

    radius += tpc_layer_thick_outer;
  }

  // outer field cage
  cyl = new PHG4CylinderSubsystem("SVTXSUPPORT", n_maps_layer + n_intt_layer + n_gas_layer);
  cyl->set_double_param("radius", radius);
  cyl->set_int_param("lengthviarapidity", 0);
  cyl->set_double_param("length", cage_length);
  cyl->set_string_param("material", "G4_KAPTON");
  cyl->set_double_param("thickness", cage_thickness);  // Kapton X_0 = 28.6 cm
  cyl->SuperDetector("SVTXSUPPORT");
  g4Reco->registerSubsystem(cyl);

  radius += cage_thickness;
	}
  // radius = 78.6464 cm
	else{
	
  double gap_betweenCZ = 1.5, Gap_betweenlayer = 1.5;
  double thickness = 0.355199;
  double BMT_outer_radius = 78.; //80;
  double BMT_inner_radius = inner_cage_radius;
  int nCZlayer = 2;
  bool use_2Dreadout = true;
  if (use_2Dreadout) {
    gap_betweenCZ = 0;
    nCZlayer = 1;
  }
  Gap_betweenlayer = (BMT_outer_radius-BMT_inner_radius-nCZlayer*thickness-gap_betweenCZ)/5.-(nCZlayer*thickness + gap_betweenCZ); // this is to create equal spaced 2D readout layers
  double BMT_mid_radius = (BMT_inner_radius+BMT_outer_radius)/2.;

  double BMT_r[6] = {BMT_inner_radius, BMT_inner_radius+nCZlayer*thickness+gap_betweenCZ+Gap_betweenlayer, BMT_mid_radius-nCZlayer*thickness-gap_betweenCZ-Gap_betweenlayer/2, BMT_mid_radius+Gap_betweenlayer/2, BMT_outer_radius-(nCZlayer*thickness+gap_betweenCZ)*2-Gap_betweenlayer, BMT_outer_radius-nCZlayer*thickness-gap_betweenCZ};
  PHG4CylinderStripSubsystem *example01;
  const double prapidity =1;
  //double bmt_length = (1-exp(-2*prapidity))/exp(-prapidity)*80;
  double bmt_length = cage_length;
  for (int ilayer = 0; ilayer< 6; ilayer++){
    example01 = new PHG4CylinderStripSubsystem("BMT",ilayer);
    example01->set_double_param("radius", BMT_r[ilayer]);
    example01->set_string_param("gas", "myMMGas");
    //example01->set_double_param("steplimits", 300e-4);
    example01->set_double_param("phi0", 15*ilayer);
    example01->set_double_param("gap", gap_betweenCZ);
    example01->SetActive();
    example01->SuperDetector("BMT");
    example01->set_int_param("lengthviarapidity",0);
    example01->set_double_param("length", bmt_length);
    example01->OverlapCheck(true);
    example01->set_int_param("use_2Dreadout",use_2Dreadout);
    g4Reco->registerSubsystem(example01);
    //example01->Print();
  }
  radius = BMT_outer_radius;
	}
	}

  return radius;
}

// Central detector cell reco is disabled as EIC setup use the fast tracking sim for now
void Svtx_Cells(int verbosity = 0)
{
  // runs the cellularization of the energy deposits (g4hits)
  // into detector hits (g4cells)

  //---------------
  // Load libraries
  //---------------

  gSystem->Load("libfun4all.so");
  gSystem->Load("libg4detectors.so");

  //---------------
  // Fun4All server
  //---------------

  Fun4AllServer* se = Fun4AllServer::instance();

  //-----------
  // SVTX cells
  //-----------

  return;
}

// Central detector  reco is disabled as EIC setup use the fast tracking sim for now
void Svtx_Reco(int verbosity = 0)
{
  //---------------
  // Load libraries
  //---------------

  gSystem->Load("libfun4all.so");

  //---------------
  // Fun4All server
  //---------------

  Fun4AllServer* se = Fun4AllServer::instance();

  return;
}
