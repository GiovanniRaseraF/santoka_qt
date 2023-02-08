while(True):
    varname = input("name")
    t = input("type")

    print("private:")
    print(f"{t} {varname};")
    print(f"std::string {varname}_str = \"{varname}\";")
    print("signals:")
    print(f"void {varname}_signal({t} newvalue);")