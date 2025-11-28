import argparse
import difflib
from itertools import zip_longest

CSI = "\033["
RESET = CSI + "0m"
RED = CSI + "31m"
GREEN = CSI + "32m"
YELLOW = CSI + "33m"

def colorize(s, color=None, enable=False):
    if not enable or color is None:
        return s
    return f"{color}{s}{RESET}"

def read_lines(path, ignore_space=False, ignore_case=False):
    with open(path, "r", encoding="utf-8-sig", errors="replace") as f:
        raw = f.read()
    norm = raw
    if ignore_case:
        norm = norm.lower()
    if ignore_space:
        # Colapsa espacios internos y quita trailing spaces por línea
        norm = "\n".join(" ".join(line.rstrip().split()) for line in norm.splitlines())
        return [line + "\n" for line in norm.splitlines()]
    else:
        # Asegura fin de línea para diffs consistentes
        lines = norm.splitlines(True)  # conserva '\n'
        # si no terminaba en \n, mantenlo así (sin agregar extra)
        return lines

def first_diff(a_lines, b_lines):
    for i, (la, lb) in enumerate(zip_longest(a_lines, b_lines, fillvalue=None), start=1):
        if la != lb:
            sa = "" if la is None else la.rstrip("\n")
            sb = "" if lb is None else lb.rstrip("\n")
            maxlen = max(len(sa), len(sb))
            for j in range(maxlen):
                ca = sa[j] if j < len(sa) else "∅"
                cb = sb[j] if j < len(sb) else "∅"
                if ca != cb:
                    return i, j + 1, sa, sb
            # solo difiere por longitudes o salto de línea
            return i, min(len(sa), len(sb)) + 1, sa, sb
    return None

def pointer_line(line_text, col):
    col = max(1, col)
    caret_line = " " * (col - 1) + "^"
    return f"{line_text}\n{caret_line}"

def highlight_char_diffs(a, b, color=False):
    """
    Devuelve dos líneas con diferencias resaltadas por carácter.
    Reemplazos: amarillo; inserciones en B: verde en B y ^ en línea guía;
    borrados desde A: rojo en A y ^ en línea guía.
    """
    sm = difflib.SequenceMatcher(a=a, b=b)
    a_out, b_out = [], []
    guide = []  # línea con ^ donde hay cambios (opcional si quieres mostrar)
    for op, a0, a1, b0, b1 in sm.get_opcodes():
        A = a[a0:a1]
        B = b[b0:b1]
        if op == "equal":
            a_out.append(A); b_out.append(B); guide.append(" " * len(B))
        elif op == "replace":
            a_out.append(colorize(A, YELLOW, color)); b_out.append(colorize(B, YELLOW, color))
            guide.append("^" * len(B if len(B) >= len(A) else A))
        elif op == "insert":
            # aparece en B, no en A
            a_out.append("")  # nada en A
            b_out.append(colorize(B, GREEN, color))
            guide.append("^" * len(B))
        elif op == "delete":
            a_out.append(colorize(A, RED, color))
            b_out.append("")  # nada en B
            guide.append("")  # sin longitud en B
    return "".join(a_out), "".join(b_out), "".join(guide)

def full_report(a_lines, b_lines, file_a, file_b, color=False):
    """
    Recorre todas las líneas y para cada diferencia imprime:
      - Nº de línea
      - Línea A con resaltado
      - Línea B con resaltado
      - Guía de ^ bajo los cambios (respecto a B)
    """
    out = []
    for i, (la, lb) in enumerate(zip_longest(a_lines, b_lines, fillvalue=None), start=1):
        if la == lb:
            continue
        sa = "" if la is None else la.rstrip("\n")
        sb = "" if lb is None else lb.rstrip("\n")
        a_h, b_h, guide = highlight_char_diffs(sa, sb, color=color)
        out.append(f"--- {file_a}:{i}")
        out.append(a_h)
        out.append(f"+++ {file_b}:{i}")
        out.append(b_h)
        if guide.strip():
            out.append(guide)
        out.append("")  # línea en blanco separadora
    if not out:
        return "✅ No hay diferencias."
    return "\n".join(out)

def unified(a_lines, b_lines, file_a, file_b, n=3):
    return "\n".join(difflib.unified_diff(
        a_lines, b_lines, fromfile=file_a, tofile=file_b, n=n, lineterm=""
    ))

def main():
    ap = argparse.ArgumentParser(description="Comparador de texto (primera diferencia, reporte completo y unified diff).")
    ap.add_argument("file_a")
    ap.add_argument("file_b")
    ap.add_argument("--ignore-space", action="store_true", help="Ignorar diferencias de espacios (colapsa espacios y remueve trailing).")
    ap.add_argument("--ignore-case", action="store_true", help="Ignorar mayúsculas/minúsculas.")
    ap.add_argument("--unified", action="store_true", help="Mostrar unified diff.")
    ap.add_argument("--context", type=int, default=3, help="Contexto para unified diff (por defecto: 3).")
    ap.add_argument("--report", action="store_true", help="Mostrar reporte completo de diferencias por línea.")
    ap.add_argument("--color", action="store_true", help="Resaltar diferencias con colores ANSI.")
    args = ap.parse_args()

    a_lines = read_lines(args.file_a, args.ignore_space, args.ignore_case)
    b_lines = read_lines(args.file_b, args.ignore_space, args.ignore_case)

    diff_info = first_diff(a_lines, b_lines)
    if diff_info is None:
        print("✅ Los archivos son idénticos con las reglas actuales.")
        return

    # Primera diferencia
    line_no, col_no, a_line, b_line = diff_info
    print("❌ Los archivos difieren.")
    print(f"Primera diferencia en línea {line_no}, columna {col_no}:\n")
    print(f"--- {args.file_a} (línea {line_no})")
    print(pointer_line(a_line, col_no))
    print()
    print(f"+++ {args.file_b} (línea {line_no})")
    print(pointer_line(b_line, col_no))
    print()

    # Reporte completo
    if args.report:
        print(colorize("Reporte completo de diferencias:", YELLOW, args.color))
        print(full_report(a_lines, b_lines, args.file_a, args.file_b, color=args.color))

    # Unified diff
    if args.unified:
        print("\nUnified diff:")
        print(unified(a_lines, b_lines, args.file_a, args.file_b, n=args.context))

if __name__ == "__main__":
    main()