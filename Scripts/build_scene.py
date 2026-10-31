"""Run once in Unreal Editor's Python console: exec(open('.../Scripts/build_scene.py').read())."""
from pathlib import Path
import unreal

root = Path(unreal.Paths.project_dir())
assets = unreal.AssetToolsHelpers.get_asset_tools()
for body in ('Moon', 'Earth'):
    source = root / 'Content' / 'SourceTextures' / (body.lower() + '.jpg')
    if not source.is_file():
        raise RuntimeError(f'Missing texture: {source}. Run Scripts/fetch_textures.py first.')
    task = unreal.AssetImportTask()
    task.set_editor_property('filename', str(source))
    task.set_editor_property('destination_path', '/Game/Textures')
    task.set_editor_property('destination_name', 'T_' + body)
    task.set_editor_property('automated', True)
    task.set_editor_property('replace_existing', True)
    task.set_editor_property('save', True)
    assets.import_asset_tasks([task])
    texture = unreal.load_asset('/Game/Textures/T_' + body)
    path = '/Game/Materials/M_' + body
    material = unreal.load_asset(path)
    if not material:
        material = assets.create_asset('M_' + body, '/Game/Materials', unreal.Material, unreal.MaterialFactoryNew())
    unreal.MaterialEditingLibrary.delete_all_material_expressions(material)
    sample = unreal.MaterialEditingLibrary.create_material_expression(material, unreal.MaterialExpressionTextureSample, -400, 0)
    sample.set_editor_property('texture', texture)
    unreal.MaterialEditingLibrary.connect_material_property(sample, 'RGB', unreal.MaterialProperty.MP_BASE_COLOR)
    roughness = unreal.MaterialEditingLibrary.create_material_expression(material, unreal.MaterialExpressionConstant, -400, 200)
    roughness.set_editor_property('r', 0.95)
    unreal.MaterialEditingLibrary.connect_material_property(roughness, '', unreal.MaterialProperty.MP_ROUGHNESS)
    unreal.MaterialEditingLibrary.recompile_material(material)
    unreal.EditorAssetLibrary.save_asset(path)

level_path = '/Game/Maps/LunarOverview'
# Preserve an existing edited map on repeat runs.
if not unreal.EditorAssetLibrary.does_asset_exist(level_path):
    levels = unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
    levels.new_level(level_path)
    actors = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
    cls = unreal.load_class(None, '/Script/ChandraNexus.LunarSystem')
    system = actors.spawn_actor_from_class(cls, unreal.Vector(0, 0, 0))
    system.set_actor_label('Earth and Moon — orbit prototype')
    light = actors.spawn_actor_from_class(unreal.DirectionalLight, unreal.Vector(0, 0, 500), unreal.Rotator(-30, -35, 0))
    light.light_component.set_editor_property('intensity', 5.0)
    light.light_component.set_editor_property('mobility', unreal.ComponentMobility.MOVABLE)
    levels.save_current_level()
unreal.log('Lunar scene prepared. Open LunarOverview and press Play.')
