# Encounter budgets

Every recipe declares act/floor bounds, base threat, allowed mutations, incompatible tags, weight, roster and stage mask. Floors are zero based. The alpha permits all named families in all three acts; act-specific roster rotation and bounded mutations provide escalation.

Budget = 2 + 4 * tier + 2 * (act - 1) + (floor % 5) / 2, using integer division. Base costs are 2/6/10 for normal/elite/boss. Remaining points buy compatible, single-use mutations at two points each: +5 damage, +5 defense, or +5 speed. Tanks cannot gain haste; fragile and speed archetypes cannot gain armor. No arbitrary tag mixing occurs. Higher tag bits record mutations in serialized encounters and run history; previews show final values and threat.

Registry generation rejects invalid ranges, rosters, composition, stage masks, weights and contradictory tags. Core tests cover all floors and tiers across 100 seeds, budget ceilings, forbidden mutation absence, reachable families, cooldowns and deterministic replay. Golden checksum: 866924df.
