# EEG

### 10-20 System

- `C` = central (Middle region of the head)
- `F` = frontal (Frontal region of the head)
- `Fp` = frontopolar (Frontal region of the head, near forehead)
- `O` = occipital (Back region of the head)
- `P` = parietal (Back region of the head)
- `T` = temporal (Outer region of the head)
- `Even` values represent electrode on `right` hemisphere (2, 4, 6, 8).
- `Odd` values represent electrode on `left` hemisphere (1, 3, 5, 7).

### Higher resolution 10 - 20 systems

- `AF` for electrodes between `Fp` and `F`
- `CP` for electrodes between `C` and `P`
- `FC` for electrodes between `F` and `C`
- `FT` for electrodes between `F` and `T`
- `PO` for electrodes between `P` and `O`
- `TP` for electrodes between `T` and `P`


| Simplified | Detailed |
|:----:|:------:|
| ![](https://github.com/CESS-Grad-Project-18/EEG/blob/Ghozlan/Figures/10_20_Detailed.png) | ![](https://github.com/CESS-Grad-Project-18/EEG/blob/Ghozlan/Figures/10_20_Simplified.png) |


### Frequency bands 

| Data | Delta | Theta | Alpha | Beta | Gamma |
|:----|:------|:------|:------|:------|:------|
| Frequency (Hz) | 1 - 4 | 4 - 8 | 8 - 12 | 12- 25 | < 25 |
| Features | <ul><li>Slowest and highest amplitude brainwaves.</li></ul><ul><li>Only present during dreamless sleep (NREM).</li></ul><ul><li>Stronger in the right brain hemisphere.</li></ul><ul><li>Localized in the thalamus.</li></ul><ul><li>Formation and internal arrangement of biographic memory as well as acquired skills and learned information.</li></ul> | <ul><li>Correlate with the difficulty of mental operations</li></ul><ul><li>Stand out as task becomes harder.</li></ul><ul><li>Serves as carrier frequency for cognitive (learning) processing across brain regions that are further apart</li></ul> | <ul><li>High power during mental and physical relaxation with eyes closed and vice versa.</li></ul><ul><li>Alpha suppression indicates that the brain is getting ready to collect information from various senses, coordinating attentional resources and focusing on what is considered relevent/important in a paticular moment.</li></ul> | <ul><li>High power during movement execution, particularly when fine finger movements is required (such as reaching out or grasping) and focused attention.</li></ul><ul><li>High power during noticing other people's body movement (Mimicing others).</li></ul> | <ul><li>Serves as a carrier frequency for binding various sensory impressions of an object together (Attention).</li></ul><ul><li>By-product of other neural processes such as eye movements and microsaccades (بترف).</li></ul> |
