DMX512 Spec

Data is transmitted sequentially in asynchronous serial format starting with slot 0 and ending with slot 512. Priot to the first data slot being transmitted, there is a reset seuence consisting of a BREAK followed by a MARK AFTER BREAK and a START code (0x00). Valid data values under a NULL START code are between 0 and 255.


