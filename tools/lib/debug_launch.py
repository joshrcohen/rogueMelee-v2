"""Validate developer launch names before creating a native debug fixture."""
import json
import tomllib
from .config import ROOT
CHARACTERS = ['captain_falcon','donkey_kong','fox','game_and_watch','kirby','bowser',
    'link','luigi','mario','marth','mewtwo','ness','peach','pikachu','ice_climbers',
    'jigglypuff','samus','yoshi','zelda','sheik','falco','young_link','dr_mario','roy','pichu','ganondorf']

def options(seed=None, scene=None, encounter=None, special=None, recipient=None, aerials=None, gold=None):
    seed = 0x524f4755 if seed is None else seed
    if not 0 <= seed < 2**64: raise ValueError('Seed must fit an unsigned 64-bit integer')
    recipient = (recipient or 'fox').lower().replace(' ','_').replace('-','_')
    if recipient not in CHARACTERS: raise ValueError('Unknown recipient; choose: '+', '.join(CHARACTERS))
    result = dict(seed=seed, scene=scene or ('encounter' if encounter or special or aerials else 'progression'), recipient=CHARACTERS.index(recipient), special=0, encounter=0, aerials=[0]*5)
    if gold is not None and not 0 <= gold <= 999999: raise ValueError('Fixture gold must be between 0 and 999999')
    result['gold'] = -1 if gold is None else gold
    catalog = json.loads((ROOT/'data/aerials.json').read_text())
    for key in aerials or []:
        matching = [r for r in catalog if r['key'] == key]
        if not matching: raise ValueError('Unknown aerial key; inspect data/aerials.json')
        move = matching[0]
        if result['aerials'][move['slot']]: raise ValueError('Choose one donor per aerial slot')
        result['aerials'][move['slot']] = move['id']
    if special:
        catalog = json.loads((ROOT/'data/specials.json').read_text())
        matching = [r for r in catalog if r['key'] == special]
        if not matching: raise ValueError('Unknown special key; inspect data/specials.json')
        result['special'] = matching[0]['id']
    if encounter:
        rows = tomllib.loads((ROOT/'data/encounters.toml').read_text())['entry']
        key = encounter.removeprefix('elite_').removeprefix('boss_')
        matching = [i+1 for i,r in enumerate(rows) if r['key'] == key]
        if not matching: raise ValueError('Unknown encounter key; inspect data/encounters.toml')
        result['encounter'] = matching[0]
    if result['scene'] not in ('progression','encounter','shop','rest'): raise ValueError('Scene must be progression, encounter, shop or rest')
    return result

def header(config=None):
    config = config or options()
    return '\n'.join([
        '#define ROGUE_FIXTURE_SEED ((((RogueSeed) %uU) << 32) | %uU)' % (config['seed'] >> 32, config['seed'] & 0xffffffff),
        '#define ROGUE_LAUNCH_RECIPIENT %u' % config['recipient'],
        '#define ROGUE_LAUNCH_SPECIAL %u' % config['special'],
        '#define ROGUE_LAUNCH_AERIALS { %s }' % ', '.join(map(str,config.get('aerials',[0]*5))),
        '#define ROGUE_LAUNCH_GOLD %d' % config.get('gold',-1),
        '#define ROGUE_LAUNCH_ENCOUNTER %u' % config['encounter'],
        '#define ROGUE_QA_PASSIVES %u' % config.get('passives',0),
        '#define ROGUE_LAUNCH_SERVICE %u' % {'shop':1,'rest':2}.get(config['scene'],0),
        '#define ROGUE_LAUNCH_COMBAT %u' % (config['scene'] == 'encounter'), ''])
