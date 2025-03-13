# Moodle kérdés: A mypy által jelzett hiba kijavítása után mi a helyes sor?

```python
#new_ciff.tags = tag #Moodle hibas sor, a tags listat kellett megadni
new_ciff.tags = tags
```

# Moodle kérdés: Melyik három tagváltozót kellett ellenőrizni, ami megoldotta a hibás tesztet? (Csak a változók nevét adja meg, vesszővel elválasztva! pl.: a, b, c)

```python
content_size, height, width
```

# Moodle kérdés: Mi annak a ciff fájlnak a neve, ami bár helyes teszt eredményt ad, mégis helytelenül fut le?

``` bash
2025-03-13 02:40:32 [    INFO] Running test on: test-images-invalid/invalid3.ciff (test_ciff.py:44)
2025-03-13 02:40:32 [   DEBUG] Expected problem: Invalid header size: header size is 0 (test_ciff.py:45)
2025-03-13 02:40:32 [   ERROR] Exception: 'ascii' codec can't decode byte 0x80 in position 0: ordinal not in range(128) (ciff.py:316)
2025-03-13 02:40:32 [    INFO] Ciff validity: False (test_ciff.py:47)
PASSED                                                                         [ 75%]
```