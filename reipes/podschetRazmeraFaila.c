WIN32_FIND_DATAA find;
    HANDLE search = FindFirstFileA("c:\\",
        &find);
    while (FindNextFileA(search, &find))
    {
        int fileSize = (find.nFileSizeHigh *
            (MAXDWORD + 1)) + find.nFileSizeLow;
        if (fileSize != 0)
        {
 
        }
    }
