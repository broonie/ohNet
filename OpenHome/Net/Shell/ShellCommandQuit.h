#ifndef HEADER_SHELL_COMMAND_QUIT
#define HEADER_SHELL_COMMAND_QUIT

#include <OpenHome/Net/Private/Shell.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Buffer.h>

#include <vector>
#include <map>

namespace OpenHome {
class IWriter;
namespace Net {

class ShellCommandQuit : private IShellCommandHandler
{
public:
    ShellCommandQuit(Shell& aShell, Semaphore& aBlocker);
    ~ShellCommandQuit();
private: // from IShellCommandHandler
    void HandleShellCommand(Brn aCommand, const std::vector<Brn>& aArgs, IWriter& aResponse);
    void DisplayHelp(IWriter& aResponse);
private:
    Shell& iShell;
    Semaphore& iBlocker;
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_SHELL_COMMAND_QUIT
