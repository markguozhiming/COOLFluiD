#ifndef COOLFluiD_SpectralFD_TVBLimiterSpectralFD_hh
#define COOLFluiD_SpectralFD_TVBLimiterSpectralFD_hh

//////////////////////////////////////////////////////////////////////////////

#include "Framework/DataSocketSink.hh"

#include "SpectralFD/BaseVolTermComputer.hh"
#include "SpectralFD/ReconstructStatesSpectralFD.hh"
#include "SpectralFD/SpectralFDMethodData.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace SpectralFD {

//////////////////////////////////////////////////////////////////////////////

/**
 * This class represent a command that applies an elementwise TVB limiter to the solution
 *
 * @author Kris Van den Abeele
 *
 */
class TVBLimiterSpectralFD : public SpectralFDMethodCom {
public:

  /**
   * Constructor.
   */
  explicit TVBLimiterSpectralFD(const std::string& name);

  /**
   * Destructor.
   */
  virtual ~TVBLimiterSpectralFD();

  /**
   * Setup private data and data of the aggregated classes
   * in this command before processing phase
   */
  virtual void setup();

  /**
   * Unsetup private data
   */
  virtual void unsetup();

  /**
   * Configures the command.
   */
  virtual void configure ( Config::ConfigArgs& args );

  /**
   * Defines the Config Option's of this class
   * @param options a OptionList where to add the Option's
   */
  static void defineConfigOptions(Config::OptionList& options);

  /**
   * Execute Processing actions
   */
  void execute();

  /**
   * Returns the DataSocket's that this command provides as sources
   * @return a vector of SafePtr with the DataSockets
   */
  std::vector< Common::SafePtr< Framework::BaseDataSocketSource > >
      providesSockets();

protected: // functions

  /**
   * reset the node min and max cell averaged states
   */
  void resetNodeNghbrCellAvgStates();

  /**
   * set the reconstruction data for averaged solution in current element type
   */
  void setAvgReconstructionData(CFuint iElemType);

  /**
   * set all the reconstruction data for current element type
   */
  void setAllReconstructionData(CFuint iElemType);

  /**
   * compute the cell averaged state
   */
  virtual void reconstructCellAveragedState();

  /**
   * compute a cell averaged variable
   */
  virtual void reconstructCellAveragedVariable(const CFuint iEq);

  /**
   * compute derivative in the cell center of a variable
   */
  virtual void computeCellCenterDerivVariable(const CFuint iEq);

  /**
   * set minimum and maximum node neighbouring cell average solutions
   * @pre reconstructCellAveragedState()
   */
  void setMinMaxNodeNghbrCellAvgStates();

  /**
   * set minimum and maximum neighbouring cell average solutions
   */
  void setMinMaxNghbrCellAvgStates();

  /**
   * check if limiting is necessary
   * @pre solution has been reconstructed at flux points
   */
  virtual void setLimitBooleans();

  /**
   * apply the limiter
   */
  virtual void limitStates();

protected: // data

  /// socket for minimum nodal state's
  Framework::DataSocketSource< RealVector > socket_nodeNghbCellMinAvgStates;

  /// socket for maximum nodal state's
  Framework::DataSocketSource< RealVector > socket_nodeNghbCellMaxAvgStates;

  /// builder of cells
  Common::SafePtr<Framework::GeometricEntityPool<Framework::StdTrsGeoBuilder> > m_cellBuilder;

  /// Strategy that reconstructs the states in a given number of nodes
  Common::SafePtr< ReconstructStatesSpectralFD > m_statesReconstr;

  /// variable for cell
  Framework::GeometricEntity* m_cell;

  /// vector containing pointers to the states in a cell
  std::vector< Framework::State* >* m_cellStates;

  /// vector containing pointers to the nodes in a cell
  std::vector< Framework::Node*  >* m_cellNodes;

  /// variable for solution in flux points
  std::vector< Framework::State* > m_solInFlxPnts;

  /// coefficients for the computation of the cell averaged solution
  Common::SafePtr< RealVector > m_cellAvgSolCoefs;

  /// coefficients for the computation of the solution derivative
  Common::SafePtr< std::vector< RealVector > > m_cellCenterDerivCoefs;

  /// reconstruction coefficients for the flux points
  Common::SafePtr< RealMatrix > m_flxPntsRecCoefs;

  /// indexes of all the flux points
  Common::SafePtr< std::vector< CFuint > > m_allFlxPntIdxs;

  /// flux point index (in the matrix flxPntRecCoefs) for reconstruction
  Common::SafePtr< std::vector< CFuint > > m_flxPntMatrixIdxForReconstruction;

  /// solution point index (in the cell) for reconstruction
  Common::SafePtr< std::vector< std::vector< CFuint > > > m_solPntIdxsForReconstruction;

  /// mapped coordinates of the solution points
  Common::SafePtr< std::vector< RealVector > > m_solPntsLocalCoords;

      /// cell averaged state
  RealVector m_cellAvgState;

  /// derivative in cell center of a physical variable
  RealVector m_cellCenterDerivVar;

  /// minimum neighbouring cell averaged state
  RealVector m_minAvgState;

  /// maximum neighbouring cell averaged state
  RealVector m_maxAvgState;

  /// minimum cell averaged state on the mesh
  RealVector m_minAvgStateAll;

  /// maximum cell averaged state on the mesh
  RealVector m_maxAvgStateAll;

  /// number of equations in the physical model
  CFuint m_nbrEqs;

  /// dimensionality of the physical model
  CFuint m_dim;

  /// number of flux points for current element type
  CFuint m_nbrFlxPnts;

  /// number of solution points for current element type
  CFuint m_nbrSolPnts;

  /// number of corner nodes for current element type
  CFuint m_nbrCornerNodes;

  /// boolean telling whether to apply the limiter
  bool m_applyLimiter;

  /// boolean telling whether to apply the limiter to a physical variable
  std::vector< bool > m_applyLimiterToPhysVar;

  /// factor used to determine whether to limit the solution
  CFreal m_tvbLimitFactor;

  /// exponent for the computation of the length scale
  CFreal m_lengthScaleExp;

}; // class TVBLimiterSpectralFD

//////////////////////////////////////////////////////////////////////////////

  } // namespace SpectralFD

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_SpectralFD_TVBLimiterSpectralFD_hh
