import Data.Monoid (mempty)
--
import FFICXX.Generate.Builder
import FFICXX.Generate.Type.Class
import FFICXX.Generate.Type.Module
import FFICXX.Generate.Type.PackageInterface


cabal = Cabal { cabal_pkgname = "STL" 
              , cabal_cheaderprefix = "STL"
              , cabal_moduleprefix = "STL" }

extraDep = [ ("Foo", ["STL.Vector.Template"]) ]


cabalattr = 
    CabalAttr 
    { cabalattr_license = Just "BSD3"
    , cabalattr_licensefile = Just "LICENSE"
    , cabalattr_extraincludedirs = [ ".." ]
    , cabalattr_extralibdirs = []
    , cabalattr_extrafiles = []
    }


vectorint_ = TemplateApp t_vector "CInt" "std::vector<int>"

class1 :: Class
class1 =
  Class cabal "Foo" [] mempty Nothing
  [ Constructor [ int "n" ] Nothing
  , Virtual void_ "showme" [] Nothing
  , Virtual vectorint_ "getVector" [] Nothing
  , Virtual void_ "addContents" [ (vectorint_, "v") ] Nothing
  ]

classes = [ class1 ]

toplevelfunctions =  [ ]  

t_vector = TmplCls cabal "Vector" "std::vector" "t"
             [ TFunNew []
             , TFun void_ "push_back" "push_back" [(TemplateParam "t","x")] Nothing
             , TFun void_ "pop_back"  "pop_back"  []                        Nothing
             , TFun (TemplateParam "t") "at" "at" [int "n"]                 Nothing
             , TFun int_  "size"      "size"      []                        Nothing
             , TFunDelete
             ]


templates = [ ( t_vector, HdrName "Vector.h" ) 
            ] 


headerMap = [ ( "Foo", ([], [HdrName "Foo.h"])) ]

main :: IO ()
main = do 
  simpleBuilder "STL" headerMap (cabal,cabalattr,classes,toplevelfunctions,templates)
    [ ] extraDep


