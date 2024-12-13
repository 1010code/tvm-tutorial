#ifndef TVMGEN_DEFAULT_H_
#define TVMGEN_DEFAULT_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief Input tensor float_input size (in bytes) for TVM module "default" 
 */
#define TVMGEN_DEFAULT_FLOAT_INPUT_SIZE 16
/*!
 * \brief Output tensor output1 size (in bytes) for TVM module "default" 
 */
#define TVMGEN_DEFAULT_OUTPUT1_SIZE 12
/*!
 * \brief Output tensor output0 size (in bytes) for TVM module "default" 
 */
#define TVMGEN_DEFAULT_OUTPUT0_SIZE 8
/*!
 * \brief Input tensor pointers for TVM module "default" 
 */
struct tvmgen_default_inputs {
  void* float_input;
};

/*!
 * \brief Output tensor pointers for TVM module "default" 
 */
struct tvmgen_default_outputs {
  void* output0;
  void* output1;
};

/*!
 * \brief entrypoint function for TVM module "default"
 * \param inputs Input tensors for the module 
 * \param outputs Output tensors for the module 
 */
int32_t tvmgen_default_run(
  struct tvmgen_default_inputs* inputs,
  struct tvmgen_default_outputs* outputs
);
/*!
 * \brief Workspace size for TVM module "default" 
 */
#define TVMGEN_DEFAULT_WORKSPACE_SIZE 474

#ifdef __cplusplus
}
#endif

#endif // TVMGEN_DEFAULT_H_
