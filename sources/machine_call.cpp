#include <machine/precompiled.h>

#include <machine/sources/machine_call.h>
#include <machine/sources/machine.h>

int MACHINE_DLL_API machine_call(
    const std::string& output_filename,
    const std::string& input_filename
)
{
    std::ofstream os(output_filename);
    std::ifstream is(input_filename);

    if (!is) {
        std::ostringstream oss;
        oss << "Could not open file \"" << input_filename << "\"";
            
        throw std::runtime_error(oss.str());
    }

    machine::Machine mc;

    is >> mc;
    os << mc;

    is.close();
    os.close();
    
    return 0;
}