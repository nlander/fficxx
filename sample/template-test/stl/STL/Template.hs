{-# LANGUAGE EmptyDataDecls #-}
{-# LANGUAGE TypeFamilies #-}

module STL.Template where

import Foreign.C.Types
-- import Foreign.ForeignPtr
import Foreign.Ptr

data RawSTLVector a

newtype STLVector a = STLVector (Ptr (RawSTLVector a))

class ISTLVector a where
  printout  :: STLVector a -> IO ()
  new       :: IO (STLVector a)
  push_back :: STLVector a -> a -> IO ()
  at        :: STLVector a -> CInt -> IO a
  delete    :: STLVector a -> IO ()

