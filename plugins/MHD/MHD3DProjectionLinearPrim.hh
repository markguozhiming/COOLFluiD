#ifndef COOLFluiD_Physics_MHD_MHD3DProjectionLinearPrim_hh
#define COOLFluiD_Physics_MHD_MHD3DProjectionLinearPrim_hh

//////////////////////////////////////////////////////////////////////////////

#include "Framework/JacobianLinearizer.hh"

//////////////////////////////////////////////////////////////////////////////

namespace COOLFluiD {

  namespace Framework {

    class State;
  }

  namespace Physics {

    namespace MHD {

      class MHDProjectionTerm;

//////////////////////////////////////////////////////////////////////////////

/**
 * This class performs all the operations related with physics-dependent
 * transformations of variables
 *
 * @author Andrea Lani
 * @author Radka Keslerova
 */
class MHD3DProjectionLinearPrim : public Framework::JacobianLinearizer {
public:

  /**
   * Default constructor without arguments
   */
  MHD3DProjectionLinearPrim(Common::SafePtr<Framework::PhysicalModel> model);

  /**
   * Default destructor
   */
  ~MHD3DProjectionLinearPrim();

  /**
   * Linearize the states
   */
  void linearize(const std::vector<Framework::State*>& statesInCell);

private:

  // physical model
  Common::SafePtr<MHDProjectionTerm> _model;

}; // end of class MHD3DProjectionLinearPrim

//////////////////////////////////////////////////////////////////////////////

    } // namespace MHD

  } // namespace Physics

} // namespace COOLFluiD

//////////////////////////////////////////////////////////////////////////////

#endif // COOLFluiD_Physics_MHD_MHD3DProjectionLinearPrim_hh
