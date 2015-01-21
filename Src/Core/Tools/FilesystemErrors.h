#pragma once

#include "Bugs/Exception.h"

namespace Tools {
namespace Filesystem {

DECLARE_EXCEPTION(FilesystemError, Bugs::Exception);
DECLARE_EXCEPTION(DirError, FilesystemError);

} // namespace Filesystem
} // namespace Tools