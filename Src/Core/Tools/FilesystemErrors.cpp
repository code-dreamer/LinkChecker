#include "stdafx.h"
#include "Tools/FilesystemErrors.h"

namespace Tools {
namespace Filesystem {

IMPLEMENT_EXCEPTION(FilesystemError, Bugs::Exception);
IMPLEMENT_EXCEPTION(DirError, FilesystemError);

} // namespace Filesystem
} // namespace Tools