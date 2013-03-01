#include <OpenHome/Private/File.h>

namespace OpenHome {

IFile* IFile::Open(const TChar* aFilename, FileMode aFileMode)
{
    return new FileAnsii(aFilename, aFileMode);
}

} // namespace OpenHome

