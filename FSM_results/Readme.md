# Deep Specification Mining Experiments
This folder contains the experimental results from [DSM](https://github.com/kanghj/DSM) technique. The sub-folders are categorized as follows:
- Sub-folders with "input" prefix are traces to test the FSM inferred by the DSM
- Sub-folders with "real" prefix are the FSM inferred by the DSM on Prius traces
- Sub-folders with "sim" prefix are the FSM inferred by the DSM on Simulation traces
- abstraction inferred state machine visualizes all the state machines inferred by abstraction based minimization algorithm

# Installation
- To run the experiments, follow the installation process from [DSM](https://github.com/kanghj/DSM). Make sure that the DSM is installed as a library
- Make a new folder named "results" in the DSM directory and copy all the sub-folders into it.
- Copy the dsm_verify.py to the DSM directory and run with python
- Comment/Uncomment the lines in dsm_verify.py to generate desired experiment results
- Per execution, it should display the number of accepted and rejected traces for the selected FSM and selected trace file
