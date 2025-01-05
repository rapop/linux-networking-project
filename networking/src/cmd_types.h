#pragma once

namespace networking {

// this is not necessary, we can set the type in the MsgTypes
// and we just need to unpack the type to know the cmd
enum class CmdTypes 
{
  StopPositionStream = 0,
};

} // namespace networking