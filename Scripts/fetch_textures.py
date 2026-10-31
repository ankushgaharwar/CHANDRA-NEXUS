"""Download pinned Three.js example textures with normal HTTPS verification."""
from pathlib import Path
from urllib.request import urlopen

ROOT = Path(__file__).resolve().parents[1] / 'Content' / 'SourceTextures'
BASE = 'https://raw.githubusercontent.com/mrdoob/three.js/r170/examples/textures/planets/'
FILES = {'moon': 'moon_1024.jpg', 'earth': 'earth_atmos_2048.jpg'}

def main():
    ROOT.mkdir(parents=True, exist_ok=True)
    for body, remote in FILES.items():
        target = ROOT / (body + '.jpg')
        if target.exists():
            continue
        with urlopen(BASE + remote, timeout=60) as response:
            data = response.read()
        if not data.startswith(b'\xff\xd8') or not data.endswith(b'\xff\xd9'):
            raise ValueError('Expected a complete JPEG: ' + remote)
        target.write_bytes(data)
        print(f'{body}: {len(data)} bytes')

if __name__ == '__main__':
    main()
