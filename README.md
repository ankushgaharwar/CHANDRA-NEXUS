# CHANDRA-NEXUS

First milestone: a textured whole Moon, Earth, sunlight, an overview camera, and a repeating lunar orbit in Unreal Engine 5.4. This is a source project; generated Unreal assets are created by the editor script.

## Open and run

1. Install Unreal Engine 5.4 and its supported C++ toolchain (Visual Studio 2022 with Game development with C++ on Windows, or the matching Unreal Linux toolchain).
2. Open `ChandraNexus.uproject` and let Unreal build the module. If needed, generate project files first and build the **ChandraNexusEditor / Development Editor** target.
3. Textures are included. To restore missing files, run `python Scripts/fetch_textures.py` from the project directory.
4. In Unreal, enable the Python Editor Script Plugin and Editor Scripting Utilities if prompted, then restart. Open **Output Log**, select **Python**, and run:

   ```python
   exec(open(unreal.Paths.project_dir() + 'Scripts/build_scene.py', encoding='utf-8').read())
   ```

5. Open `/Game/Maps/LunarOverview` and press **Play**. The camera frames the system. The Moon completes one orbit in 120 seconds and keeps the same face toward Earth. Escape returns to the editor.
6. Select the LunarSystem actor and adjust **Orbit Radius**, **Orbit Period Seconds**, or **Paused**. Both bodies use replaceable materials in `/Game/Materials`.

The startup map does not exist until step 4. On the first launch, a missing-map warning can therefore appear. The setup script preserves an existing map, but rebuilds the two generated materials; duplicate those materials before customizing them.

## Scope and scale

Body radii preserve the approximate Earth/Moon ratio: 6,371 km and 1,737.4 km. One scene unit represents 100 km; default orbital distance is compressed from 384,400 km to 35,000 km for presentation. Set Orbit Radius to 3844 for the mean physical distance, then move the camera to frame it. Time is accelerated. The orbit is circular and coplanar; eccentricity, inclination, libration, Earth rotation, atmosphere, and gravitational simulation are not implemented.

The Moon is Unreal's built-in UV sphere with a photographic color texture and rough material. It has no terrain elevation or modeled craters yet. The dark background is space; sunlight supplies the day/night boundary. There is no external service or API key dependency at runtime.

## Terrain direction

Use Moon-fixed latitude/longitude in degrees and elevations in meters for future data ingestion. Proposed convention: +Z north, +X at latitude 0 / longitude 0, +Y at east longitude 90. Position is `(R+h) * (cos(lat)*cos(lon), cos(lat)*sin(lon), sin(lat))`; convert units only at the rendering boundary.

**The current engine sphere UVs and texture prime meridian have not been geodetically calibrated.** Before adding Shackleton or other named features, replace/calibrate the globe mesh and texture against known landmarks, establish the source datum, and verify latitude/longitude handedness. Do not position scientific sectors from this visual placeholder alone.

Suggested milestones, with timing left flexible:

- First month: open and validate this prototype, camera navigation, calibrated lunar coordinates and texture orientation.
- Following months: authoritative global color/elevation data, a terrain tile loader, and one correctly located south-pole sector.
- Longer term: successive sectors, seams and levels of detail, close-up rendering, provenance and accuracy checks per dataset, then application-specific simulation tools.

Avoid importing every detailed sector at once: use streamed tiles once terrain work begins.

## Asset provenance

`Content/SourceTextures/moon.jpg` and `earth.jpg` are the Moon and Earth example textures from the Three.js r170 repository:

- https://github.com/mrdoob/three.js/blob/r170/examples/textures/planets/moon_1024.jpg
- https://github.com/mrdoob/three.js/blob/r170/examples/textures/planets/earth_atmos_2048.jpg
- Three.js repository license: https://github.com/mrdoob/three.js/blob/r170/LICENSE

These are visualization assets, not a surveyed lunar surface dataset. Retain upstream attribution and check asset-specific provenance before redistribution in a released product.

## Validation status

Python scripts were syntax-checked and texture downloads completed with HTTPS verification. Unreal Editor is unavailable in the cloud environment used to create this project, so C++ compilation, editor API compatibility, UV appearance, lighting, and Play-in-Editor behavior remain unverified. Required local acceptance: build the editor target, run the scene script, confirm both textured bodies render, and observe a complete orbit with synchronous rotation.
