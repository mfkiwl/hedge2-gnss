// ======================================================================
// \title  gnssRpiTopology.hpp
// \brief header file containing the topology instantiation definitions
//
// ======================================================================
#ifndef GNSSRPI_GNSSRPITOPOLOGY_HPP
#define GNSSRPI_GNSSRPITOPOLOGY_HPP
// Included for access to gnssRpi::TopologyState and gnssRpi::ConfigObjects::pingEntries. These definitions are required by the
// autocoder, but are also used in this hand-coded topology.
#include <gnssRpi/Top/gnssRpiTopologyDefs.hpp>

// Remove unnecessary gnssRpi:: qualifications
using namespace gnssRpi;
namespace gnssRpi {
/**
 * \brief initialize and run the F´ topology
 *
 * Initializes, configures, and runs the F´ topology. This is performed through a series of steps, some provided via
 * autocoded functions, and others provided via the functions implementation. These steps are:
 *
 *   1. Call the autocoded `initComponents()` function initializing each component via the `component.init` method
 *   2. Call the autocoded `setBaseIds()` function to set the base IDs (offset) for each component instance
 *   3. Call the autocoded `connectComponents()` function to wire-together the topology of components
 *   4. Configure components requiring custom configuration
 *   5. Call the autocoded `loadParameters()` function to cause each component to load initial parameter values
 *   6. Call the autocoded `startTasks()` function to start the active component tasks
 *   7. Start tasks not owned by active components
 *
 * Step 4 and step 7 are custom and supplied by the project. The ordering of steps 1, 2, 3, 5, and 6 are critical for
 * F´ topologies to function. Configuration (step 4) typically assumes a connect but not started topology and is thus
 * inserted between step 3 and 5. Step 7 may come before or after the active component initializations. Since these
 * custom tasks often start radio communication it is convenient to start them last.
 *
 * The state argument carries command line inputs used to setup the topology. For an explanation of the required type
 * gnssRpi::TopologyState see: gnssRpiTopologyDefs.hpp.
 *
 * \param state: object shuttling CLI arguments (e.g. hostname/port, or UART baudrate) needed to construct the topology
 */
void setupTopology(const TopologyState& state);

/**
 * \brief teardown the F´ topology
 *
 * Tears down the F´ topology in preparation for shutdown. This is done via a series of steps, some provided by
 * autocoded functions, and others provided via the function implementation. These steps are:
 *
 *   1. Call the autocoded `stopTasks()` function to stop the tasks started by `startTasks()` (active components)
 *   2. Call the autocoded `freeThreads()` function to join to the tasks started by `startTasks()`
 *   3. Stop the tasks not owned by active components
 *   4. Join to the tasks not owned by active components
 *   5. Deallocate other resources
 *
 * Step 1, 2, 3, and 4 must occur in-order as the tasks must be stopped before being joined. These tasks must be stopped
 * and joined before any active resources may be deallocated.
 *
 * For an explanation of the required type gnssRpi::TopologyState see: gnssRpiTopologyDefs.hpp.
 *
 * \param state: state object provided to setupTopology
 */
void teardownTopology(const TopologyState& state);

/**
 * \brief cycle the rate group driver at a crude rate
 *
 * The reference topology does not have a true 1Hz input clock for the rate group driver because it is designed to
 * operate across various computing endpoints (e.g. laptops) where a clear 1Hz source may not be easily and generically
 * achieved. This function mimics the cycling via a Task::delay(milliseconds) loop that manually invokes the ISR call
 * to the example block driver.
 *
 * This loop is stopped via a startSimulatedCycle call.
 *
 * Note: projects should replace this with a component that produces an output port call at the appropriate frequency.
 *
 * \param milliseconds: milliseconds to delay for each cycle. Default: 1000 or 1Hz.
 */
void startSimulatedCycle(Fw::TimeInterval interval = Fw::TimeInterval(1,0));

/**
 * \brief stop the simulated cycle started by startSimulatedCycle
 *
 * This stops the cycle started by startSimulatedCycle.
 */
void stopSimulatedCycle();

} // namespace gnssRpi
#endif
