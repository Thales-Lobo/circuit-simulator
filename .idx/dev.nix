{ pkgs, ... }: {
  channel = "stable-23.05"; # "stable-23.05" or "unstable"
  packages = [
    pkgs.nodejs
    pkgs.nodePackages.firebase-tools
    pkgs.cmake
    pkgs.emscripten
    pkgs.yarn
    pkgs.docker
  ];
  idx.extensions = [
  ];
  idx.previews = {
    enable = true;
    previews = [
      {
        command = ["npm" "run" "dev" "--" "--port" "$PORT" "--hostname" "0.0.0.0"];
        manager = "web";
        id = "web";
      }
    ];
  };
  services.docker.enable = true;
}