{
  description = "PGK2 - 3D Arkanoid";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    engine = { url = "github:rafal11ck/opengl-3d-engine"; flake = false; };
    glText = { url = "github:vallentin/glText"; flake = false; };
  };

  outputs = { self, nixpkgs, engine, glText }:
    let
      pkgs = nixpkgs.legacyPackages.x86_64-linux;
    in
    {
      packages.x86_64-linux.default = pkgs.stdenv.mkDerivation {
        pname = "pgk2";
        version = "0.1.0";
        src = ./.;

        nativeBuildInputs = [ pkgs.cmake ];
        buildInputs = with pkgs; [ sfml_2 glew glm stb libGL ];

        # w sandboxie nie ma internetu, wiec podajemy zrodla zamiast FetchContent
        cmakeFlags = [
          "-DFETCHCONTENT_SOURCE_DIR_ENGINE=${engine}"
          "-DFETCHCONTENT_SOURCE_DIR_GL_TEXT=${glText}"
        ];

        meta.mainProgram = "main";
      };

      devShells.x86_64-linux.default = pkgs.mkShell {
        inputsFrom = [ self.packages.x86_64-linux.default ];
        packages = with pkgs; [ gdb clang-tools ];
      };
    };
}
