Makra napisane przez Zofia Juda, 02.01.2025 Folder zawiera makra napisane w środowisku ROOT. Aby móc je uruchomić należy mieć zainstalowane środowisko root.

Makro zadanie_1.C czytane dane z pliku  wave_0.dat, na postawie którego odczytuje pierwsze 1024 liczby i rysuje histogram na kanwie.
Aby odczytać kolejne dane należy dwukronie kliknąć na kanwę.
Ponadto po uruchomieniu program zapyta się, co ile obejrzanych widm ma się zapytać czy wyjść z programu,  należy podać liczbę. 
Ta opcja pozwala na zamknięcie programu po obejrzeniu podanej liczby histogramów, albo kontyunowanie oglądania.
Dodatkowo program zapyta się czy chcemy przesunąć baseline (odpowiedż y - tak odpowiedź n- nie).
Ta opcja spowoduje przesunięcie histogramu do poziomu 0, a przesunięcie wypisze w okienku na histogramie.
Jako argument funckja bierze nazwę pliku z którego ma czytać dane, domyślnie jest to plik wave_0.dat. Makro można uruchomić w następujące sposoby:

 `root zadanie_1.C` -> makro uruchomi się z domyślnym argumentem

w sesji root'a poprzez `.x zadanie_1.C` -> również uruchomi się z domyślnym argumentem

w sesji root poprzez:

`.L WidmoCs.C` => ładowanie makra

`WidmoCs("nazwa_pliku");` -> ta opcja umożliwa uruchomienie programu z innym argumentem
