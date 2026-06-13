defmodule SumDigits do
  def run do
    n = IO.gets("") |> String.trim() |> String.to_integer()
    numbers = IO.gets("") |> String.trim() |> String.split() |> Enum.map(&String.to_integer/1)
    
    result = Enum.reduce(numbers, 0, fn num, acc ->
      acc + sum_digits(num)
    end)
    
    IO.puts(result)
  end
  
  defp sum_digits(0), do: 0
  defp sum_digits(num) do
    digit = rem(num, 10)
    rest = div(num, 10)
    if rem(digit, 3) == 0 do
      digit + sum_digits(rest)
    else
      sum_digits(rest)
    end
  end
end

SumDigits.run()
