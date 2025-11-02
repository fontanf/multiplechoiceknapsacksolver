import gdown
import pathlib
import py7zr

gdown.download(id="1QXy0JVxUHk-vJ0kN87FoA5_NlRjYlWwj", output="data.7z")
with py7zr.SevenZipFile("data.7z", mode="r") as z:
    z.extractall(path="data")
pathlib.Path("data.7z").unlink()
