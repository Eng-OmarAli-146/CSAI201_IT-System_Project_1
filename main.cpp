// ============================================================================
// main.cpp
// Asks for the mode and the file names, loads the input and runs the simulation.
// ============================================================================
#include "Definitions.h"
#include "InputReader.h"
#include "Simulation.h"

int main()
{
    // 1) interactive or silent
    cout << "Choose mode [I=Interactive, S=Silent]: ";
    string modeLine;
    getline(cin, modeLine);

    bool interactive = false;
    if (!modeLine.empty() && (modeLine[0] == 'I' || modeLine[0] == 'i'))
        interactive = true;

    // 2) input file name (Enter = default)
    cout << "Enter input file name [input.txt]: ";
    string inputName;
    getline(cin, inputName);
    if (inputName.empty()) inputName = "input.txt";

    // 3) output file name (Enter = default)
    cout << "Enter output file name [output.txt]: ";
    string outputName;
    getline(cin, outputName);
    if (outputName.empty()) outputName = "output.txt";

    // 4) load the input file (the reader prints the reason if it fails)
    InputReader reader(inputName);
    if (!reader.LoadFile())
        return 1;

    // 5) run the simulation (it writes the output file at the end)
    Simulation sim(&reader, interactive, outputName);
    sim.Run();

    return 0;
}
