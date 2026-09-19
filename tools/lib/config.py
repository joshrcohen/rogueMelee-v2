import os
from pathlib import Path
import tomllib

ROOT = Path(__file__).resolve().parents[2]


def load(root=ROOT):
    path = root / "config/local.toml"
    cfg = tomllib.loads(path.read_text(encoding="utf-8")) if path.exists() else {}
    paths = cfg.setdefault("paths", {})
    build = cfg.setdefault("build", {})
    for key, env in (("melee_iso", "MELEE_ISO_PATH"), ("dolphin", "DOLPHIN_PATH")):
        if os.environ.get(env):
            paths[key] = os.environ[env]
    build["jobs"] = int(os.environ.get("ROGUEMELEE_BUILD_JOBS", build.get("jobs", 8)))
    if not 1 <= build["jobs"] <= 256:
        raise ValueError("Build jobs must be between 1 and 256")
    if not paths.get("melee_iso"):
        images = sorted((root / ".iso").glob("*.iso")) + sorted((root / ".iso").glob("*.gcm"))
        if len(images) == 1:
            paths["melee_iso"] = str(images[0])
    return cfg
