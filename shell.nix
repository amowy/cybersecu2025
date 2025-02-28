let
  # https://status.nixos.org.
  pkgs = import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/cf8cc1201be8bc71b7cbbbdaf349b22f4f99c7ae.tar.gz") {};
in pkgs.mkShell {
  packages = [
    (pkgs.python3.withPackages (python-pkgs: with python-pkgs; [
      tkinter
      pillow
      pybind11
      setuptools
    ]))
    pkgs.gcc
  ];

  shellHook = ''
    export CPLUS_INCLUDE_PATH=$(python -c "import pybind11; print(pybind11.get_include())"):$CPLUS_INCLUDE_PATH
    echo "Pybind11 include path set: $CPLUS_INCLUDE_PATH"
    
    if [ ! -f "build/lib.*-*/ciff.*.so" ]; then
      echo "Building and installing CIFF package..."
      python setup.py build
      python setup.py install --user
      export PYTHONPATH=~/.local/lib/python3.$(python3 -c 'import sys; print(sys.version_info.minor)')/site-packages:$PYTHONPATH
      echo "CIFF package installed successfully!"
    else
      echo "CIFF package already built."
    fi
  '';
}