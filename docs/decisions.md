# Implementation decisions

- Use the provided empty rogueMelee-v2 workspace as the fresh repository rather than creating another folder.
- Sections 29–34 determine execution order and resolve earlier provisional values. Reward rerolls start at 15 gold with a 10 gold step; shop rerolls start at 25 with a 15 gold step.
- Keep the user-provided image in `.iso/`, ignored by Git, and access it read-only.
- Aerial swapping and external competitive AI remain post-alpha work as specified.
