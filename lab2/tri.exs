defmodule Water do
  def run do
    [n, m] = IO.gets("") |> String.trim() |> String.split() |> Enum.map(&String.to_integer/1)
    
    {total, _, steps, history} = simulate(n, m, 0, 0, 0, [])
    
    IO.puts("#{total} #{steps}")
    Enum.each(history, fn row ->
      IO.puts(Enum.join(row, " "))
    end)
  end
  
  defp simulate(full, m, total, empty, steps, history) when full > 0 do
    row = List.duplicate(1, full) ++ List.duplicate(0, empty)
    new_history = history ++ [row]
    new_total = total + full
    new_empty = empty + full
    new_steps = steps + 1
    
    if new_empty >= m and new_empty > 0 do
      exchange = div(new_empty, m)
      remainder = rem(new_empty, m)
      before_row = List.duplicate(1, 0) ++ List.duplicate(0, new_empty)
      simulate(exchange, m, new_total, remainder, new_steps + 1, new_history ++ [before_row])
    else
      {new_total, 0, new_steps, new_history}
    end
  end
  
  defp simulate(0, _, total, empty, steps, history) do
    if empty > 0 do
      row = List.duplicate(0, empty)
      {total, 0, steps, history ++ [row]}
    else
      {total, 0, steps, history}
    end
  end
end

Water.run()