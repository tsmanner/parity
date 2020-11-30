{
  pkgs ? import <nixpkgs> {},
  ...
}: with pkgs; with lib; {
  include = stdenv.mkDerivation {
    name = "parity-include";
    src = builtins.filterSource (path: type: baseNameOf path != ".git" && ((type == "directory") || (lib.strings.hasSuffix ".hpp" path))) ./.;
    buildCommand = ''
      ln -s $src $out
    '';
  };
}
